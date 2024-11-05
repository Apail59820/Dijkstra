//
// Created by Amaury Paillard on 05/11/2024.
//

#ifndef GUI_H
#define GUI_H

class Gui final {
public:
    Gui();
    ~Gui();

    void Render();

private:
    char mapPointNameInput[12] = {"Point"};
};

#endif //GUI_H
