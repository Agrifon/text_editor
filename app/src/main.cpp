#include <core/document.h>
#include <iostream>

int main()
{
    core::Document doc;
    doc.setText("test string");
    std::cout << "Text: " << doc.text() << std::endl;
    
    std::string filename = "test.txt";
    if(doc.save(filename))
    {
        std::cout << "File saved successfully: " << filename << std::endl;
    }
    else
    {
        std::cerr << "Failed to save file!" << std::endl;
        return 1;
    }

    core::Document loadedDoc;
    if(loadedDoc.load(filename))
    {
        std::cout << "File loaded successfully. Content: " << loadedDoc.text() << std::endl;
    }
    else
    {
        std::cerr << "Failed to load file!" << std::endl;
        return 1;
    }

    return 0;
}

