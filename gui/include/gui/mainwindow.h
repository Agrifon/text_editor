#pragma once

#include <QMainWindow>

namespace core {class Document;}
class QTextEdit;

namespace gui
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT
        
        private slots:
            void newDocument();
            void openDocument();
            void saveDocument();
            void saveDocumentAs();
            void exitApp();
            void onTextChanged();
        
        private:
            void createMenuBar();
            void updateEditor(); 
            void updateWindowTitle(); 
            bool maybeSave();            

            core::Document* m_document;
            QTextEdit* m_textEdit;

        protected:
            void closeEvent(QCloseEvent* event) override;
        
        public:
            explicit MainWindow(core::Document* document, QWidget* parent = nullptr);   
            ~MainWindow(); 
    };
}

