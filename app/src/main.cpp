#include <QApplication>
#include <core/document.h>
#include <gui/mainwindow.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Text Editor");
    app.setOrganizationName("Vladislav Zheleznyak");

    core::Document doc;

    if(argc > 1 && !doc.load(argv[1]))
    {
        qWarning() << "Could not load file" << argv[1];
    }

    gui::MainWindow window(&doc);
    window.show();

    return app.exec();
}

