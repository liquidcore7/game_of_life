//
// Created by liquidcore7 on 30.01.18.
//

#ifndef LIFE_GUI_H
#define LIFE_GUI_H

#include <nana/gui.hpp>
#include <vector>
#include <nana/gui/widgets/form.hpp>
#include <cmath>
#include <cassert>
#include "logic.h"

class Field : public nana::nested_form
{
    std::vector<bool> lives;
    const size_t cells;
    nana::drawing drw;

    void update_field()
    {
        drw.clear();
        size_t x = this->size().width / cells,
                y = this->size().height / cells;

        for (size_t i = 0; i < cells; ++i) {
            for (size_t j = 0; j < cells; ++j) {
                if (lives.at(i * cells + j))
                    drw.draw([i, j, x, y] (nana::paint::graphics g) {
                        nana::rectangle curr(i * x, j * y, x, y);
                        g.rectangle(curr, true, nana::colors::black);
                        g.rectangle(curr, false, nana::colors::wheat);
                    });
            }
        }
        drw.update();
    }

public:
    explicit Field(nana::form& parent, const std::vector<bool> &arg) :
            nana::nested_form{parent},
            lives(arg), drw{*this},
            cells(static_cast<size_t>(std::sqrt(arg.size())))
    {
        this->bgcolor(nana::colors::wheat);
        this->events().resized([this] (nana::arg_resized res)
                               {
                                   update_field();
                               });
        update_field();
    }

    void next_state()
    {
        next_population(lives);
        update_field();
    }
};


#endif //LIFE_GUI_H
