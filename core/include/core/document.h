#pragma once

#include<string>

namespace core
{
    class Document
    {
        private:
            std::string m_text;
            std::string m_filename;
            bool m_isModified = false;

        public:
            Document() = default;
            ~Document() = default;
    
            std::string text() const;
            void setText(const std::string& newText);

            bool load(const std::string& filename);
            bool save(const std::string& filename);
            bool saveAs(const std::string& filename);

            std::string fileName() const;
            void setFileName(const std::string& name);

            bool isModified() const;
            void setModified(bool modified);

    };
}
