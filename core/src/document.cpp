#include "core/document.h"

#include <fstream>
#include <sstream>

std::string core::Document::text() const
{
    return m_text;
}

void core::Document::setText(const std::string& newText)
{
    m_text = newText;
}

bool core::Document::load(const std::string& filename)
{
    std::ifstream file(filename);

    if(!file.is_open()) return false;

    std::stringstream buffer;
    buffer << file.rdbuf();
    m_text = buffer.str();
    m_filename = filename;
    return true;
}

bool core::Document::save(const std::string& filename) const
{
    std::ofstream file(filename);
    if(!file.is_open()) return false;
    file << m_text;
    return true;
}

