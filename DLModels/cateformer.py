import torch
import torch.nn as nn
from typing import List, Tuple


class CateFormer(nn.Module):
    def __init__(
        self,
        input_size: int,
        hidden_size: int,
        output_size: int,
        n_feature_selector: int,
        num_layers: int,
        nhead: int,
        dropout: float,
        dim_feedforward: int,
        catelist: List,
        bias: bool,
        n_predefined: int,
    ):
        super().__init__()
        # Fc in
        self.fc_in = nn.Linear(input_size, hidden_size, bias)
        self.fc_in_list = nn.ModuleList(
            [nn.Linear(input_size, hidden_size, bias) for _ in n_feature_selector]
        )

        # category embedding layers
        self.emb_layers = nn.ModuleList(
            [nn.Embedding(catelist[i], hidden_size, padding_idx=0) for i, _ in enumerate(catelist)]
        )

        # Encoder Layer
        encoder_layer = nn.TransformerEncoderLayer(
            d_model=hidden_size,
            nhead=nhead,
            dim_feedforward=dim_feedforward,
            activation="gelu",
            dropout=dropout,
        )
        self.encoder = nn.TransformerEncoder(
            encoder_layer=encoder_layer,
            num_layers=num_layers,
        )

        # Decoder Layer
        decoder_layer = nn.TransformerDecoderLayer(
            d_model=hidden_size,
            nhead=nhead,
            dim_feedforward=dim_feedforward,
            activation="gelu",
            dropout=dropout,
        )
        self.decoder = nn.TransformerDecoder(
            decoder_layer=decoder_layer,
            num_layers=num_layers,
        )

        # hidden learnable parameters
        self.hidden_vector = nn.Parameter(torch.randn(n_predefined, hidden_size))

        # Fc out
        self.fc_out_1 = nn.Linear(hidden_size, hidden_size // 2, bias)
        self.fc_out_2 = nn.Linear(hidden_size // 2, output_size, bias)

        self.activation = nn.GELU()


    def forward(self, x: torch.Tensor, x_cate: torch.Tensor) -> torch.Tensor:
        bs = x.shape[0]
        x = self.fc_in(x) # [bs, seq_len, hidden]
        x = x.permute(1, 0, 2) # [seq_len, bs, hidden]
        x = self.encoder(x) # [seq_len, bs, hidden]

        # [bs, len(catelist), hidden]
        x_cate = torch.cat([emb(x_cate[:, idx]).unsqueeze(1) for idx, emb in enumerate(self.emb_layers)], dim=1)
        x_cate = x_cate.permute(1, 0, 2) # [len(catelist), bs, hidden]

        hidden_vector = self.hidden_vector.unsqueeze(0)
        hidden_vector = hidden_vector.repeat(bs, 1, 1)
        hidden_vector = hidden_vector.permute(1, 0, 2)

        x = self.decoder(x, torch.cat([x_cate, hidden_vector], dim=0)) # 
        x = x[-1, :, :]
        x = self.fc_out_1(x)
        x = self.activation(x)
        x = self.fc_out_2(x)

        return x.squeeze(-1)


if __name__ == '__main__':
    
    # x = torch.randn(4000, 4, 962)
    # x_int = torch.randint(0, 50, (4000, 4))
    # model = CateQuery(
    #     input_size=962,
    #     hidden_size=32,
    #     output_size=1,
    #     catelist=[50, 50, 50, 50],
    #     num_layers=6,
    #     dropout=0.4,
    # )

    x_cate = torch.randint(0, 50, (4000, 3))
    x = torch.randn(4000, 4, 200)
    model = CateFormer(
        input_size=200,
        hidden_size=128,
        output_size=1,
        num_layers=3,
        nhead=4,
        dropout=0.4,
        dim_feedforward=128,
        catelist=[50,50,50],
        bias=True,
        n_predefined=10
    )
    y = model(x, x_cate)
    print(y.shape)