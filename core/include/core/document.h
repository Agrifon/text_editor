#pragma once
#include<string>

namespace core
{
    class Document
    {
        private:
            std::string m_text;
            std::string m_filename;

        public:
            Document() = default;
            ~Document() = default;
    
            std::string text() const;
            void setText(const std::string& newText);

            bool load(const std::string& filename);
            bool save(const std::string& filename) const;

    };
}
