//
// Created by Kernux on 1/31/2021.
//

#include "src/headers/JsProvider.h"

void JsProvider::setText(const QString &text)
{
    this->m_text = text;
    emit textChanged(m_text);
}
