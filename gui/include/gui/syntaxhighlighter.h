#pragma once

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

namespace gui
{

    class SyntaxHighlighter : public QSyntaxHighlighter
    {
        Q_OBJECT

        public:
            explicit SyntaxHighlighter(QTextDocument* parent = nullptr);

        protected:
            void highlightBlock(const QString& text) override;

        private:
            struct HighlightingRule
            {
                QRegularExpression pattern;
                QTextCharFormat format;
            };

        QVector<HighlightingRule> highlightingRules;

        QTextCharFormat keywordFormat;
        QTextCharFormat stringFormat;
        QTextCharFormat commentFormat;
        QTextCharFormat numberFormat;
        QTextCharFormat preprocessorFormat;

        QRegularExpression commentStartExpression;
        QRegularExpression commentEndExpression;
    };
}
