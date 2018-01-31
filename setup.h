//
// Created by liquidcore7 on 31.01.18.
//

#ifndef LIFE_SETUP_H
#define LIFE_SETUP_H

#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <memory>

class Setup : public nana::form
{
    std::vector<std::shared_ptr<nana::checkbox>> storage;
    size_t cells;
    nana::place markup;
    nana::button ok;

    std::vector<bool> transform() const
    {
        std::vector<bool> ret(cells * cells);
        for (size_t i = 0; i < cells * cells; ++i)
            ret[i] = storage[i].get()->checked();
        return ret;
    }

public:
    Setup(size_t sz, std::vector<bool>& k) : cells(sz), markup(*this), ok{*this, "OK"}
    {
        this->bgcolor(nana::colors::wheat);
        std::stringstream ss;
        ss << "<chk grid=[" << sz << ',' << sz << "]>|10%<ok>";
        markup.div(ss.str().c_str());
        for (size_t i = 0; i < sz * sz; ++i) {
            auto tmp = std::shared_ptr<nana::checkbox>(new nana::checkbox(*this));
            tmp->bgcolor(nana::colors::wheat);
            storage.push_back(tmp);
            markup.field("chk") << storage.back()->handle();
        }

        ok.events().click([this, &k] () {
            k = transform();
            nana::API::exit();
        });

        markup.field("ok") << ok;
        markup.collocate();
    }
};

#endif //LIFE_SETUP_H
