#include <iostream>
#include <bits/stdc++.h>
#include <functional>


void keyevent(int keycode, int status) {
    std::cout << "keycode = " << keycode << " status = " << status << std::endl;
}


int main() {
    std::function<void(int, int)> callback_keyevent = nullptr;
    callback_keyevent = keyevent;

    // if (callback_keyevent)
    // callback_keyevent(1, 0);

    callback_keyevent(1, 0);

    return 0;
}



