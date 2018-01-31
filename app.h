//
// Created by liquidcore7 on 30.01.18.
//

#ifndef LIFE_APP_H
#define LIFE_APP_H

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <thread>
#include <zconf.h>
#include "pthread.h"
#include "field.h"

void* update_routine(void* fld)
{
    while (1) {
        sleep(1);
        Field* k = (Field*) fld;
        k->next_state();
    }
}

class App : public nana::form
{
    pthread_t updater;
    nana::place layout;
    nana::button next;
    nana::checkbox auto_upd;
    Field field;

public:
    App(const std::vector<bool>& init) :
            field{*this, init},
            layout{*this},
            next{*this, "Next state"},
            auto_upd{*this, "Auto-update"}
    {
        auto_upd.check(false);

        auto_upd.events().click([this] () {
            if (auto_upd.checked())
            {
                pthread_create(&updater, NULL, &update_routine, (void*)(&this->field));
                pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
                pthread_detach(updater);
            }
            else {
                pthread_cancel(updater);
            }
        });

        next.events().click([this] () {
           field.next_state();
        });

        layout.div("vert<field>|10%<<box>|40%<btn>>");
        layout["field"] << field;
        layout["box"] << auto_upd;
        layout["btn"] << next;
        layout.collocate();
    }

};


#endif //LIFE_APP_H
