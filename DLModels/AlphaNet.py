import torch
import torch.nn as nn

"""
https://crm.htsc.com.cn/doc/2020/10750101/74856806-a2e3-41cb-be4c-695dc6cc1341.pdf

Idea:
x: Imagine the input data as tabular data
x: [batch_size, seqlen, feature_size]
y: return rate
y: [batch_size, number_of_returns]
"""

class AlphaNet(nn.Module):
    def __init__(
        self,
        input_channel,
        fc1_neuron,
        fc2_neuron,
        fcast_neuron,
    ):
        super().__init__()
        self.fc1_neuron = fc1_neuron
        self.fc2_neuron = fc2_neuron
        self.fcast_neuron = fcast_neuron
        self.batchnorm = nn.BatchNorm2d(input_channel)
        self.dropout = nn.Dropout(0.5)
        self.fc1 = nn.Linear(self.fc1_neuron, self.fc2_neuron)
        self.out = nn.Linear(self.fc2_neuron, self.fcast_neuron)
        self.relu = nn.ReLU()

    def 
    # def forward(self, data, num, num_rev):
        # conv1 = self.ts_con

if __name__ == '__main__':
    input_data = torch.randn(10, 3, 28, 28)
