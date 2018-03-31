/* 
 * File:   MarkableTextBox.hpp
 * Author: sg
 *
 * Created on 27. März 2018, 16:38
 */

#ifndef MARKABLETEXTBOX_HPP
#define MARKABLETEXTBOX_HPP

class MarkableTextBox {
public:
    struct Mark {
        int begin;
        int length;
    };
    MarkableTextBox();
    MarkableTextBox(const MarkableTextBox& orig);
    virtual ~MarkableTextBox();
private:

};

#endif /* MARKABLETEXTBOX_HPP */

