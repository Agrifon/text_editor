#include "core/document.h"

#include <fstream>
#include <sstream>

std::string core::Document::text() const
{
    return m_text;
}

void core::Document::setText(const std::string& newText)
{   
    if(m_text != newText)
    {
        m_text = newText;
        m_isModified = true;
    }
}

bool core::Document::load(const std::string& filename)
{
    std::ifstream file(filename);

    if(!file.is_open()) return false;

    std::stringstream buffer;
    buffer << file.rdbuf();
    m_text = buffer.str();
    m_filename = filename;
    m_isModified = false;
    return true;
}

bool core::Document::save(const std::string& filename) const
{
    std::ofstream file(filename);
    if(!file.is_open()) return false;
    file << m_text;
    return true;
}

bool core::Document::saveAs(const std::string& filename)
{
    if(!save(filename)) return false;
    m_filename = filename;
    m_isModified = false;
    return true;
}

std::string core::Document::fileName()const
{
    return m_filename;
}

void core::Document::setFileName(const std::string& name)
{
    m_filename = name;
}

bool core::Document::isModified() const
{
    return m_isModified;
}

void core::Document::setModified(bool modified)
{
    m_isModified = modified;
}

