#include "gui/syntaxhighlighter.h"

#include <QColor>

gui::SyntaxHighlighter::SyntaxHighlighter(QTextDocument* parent)
    :QSyntaxHighlighter(parent)
{
    keywordFormat.setForeground(QColor(0,0,255));
    keywordFormat.setFontWeight(QFont::Bold);

    const QStringList keywordPatterns = {
    "\\bchar\\b", "\\bclass\\b", "\\bconst\\b", "\\bdouble\\b",
    "\\benum\\b", "\\bexplicit\\b", "\\bfriend\\b", "\\binline\\b",
    "\\bint\\b", "\\blong\\b", "\\bnamespace\\b", "\\boperator\\b",
    "\\bprivate\\b", "\\bprotected\\b", "\\bpublic\\b", "\\breturn\\b",
    "\\bshort\\b", "\\bsigned\\b", "\\bsizeof\\b", "\\bstatic\\b",
    "\\bstruct\\b", "\\btemplate\\b", "\\bthis\\b", "\\btypedef\\b",
    "\\btypename\\b", "\\bunion\\b", "\\bunsigned\\b", "\\bvirtual\\b",
    "\\bvoid\\b", "\\bvolatile\\b", "\\bwhile\\b", "\\bif\\b",
    "\\belse\\b", "\\bswitch\\b", "\\bcase\\b", "\\bbreak\\b",
    "\\bcontinue\\b", "\\bdefault\\b", "\\bdo\\b", "\\bfor\\b",
    "\\bgoto\\b", "\\btry\\b", "\\bcatch\\b", "\\bthrow\\b",
    "\\bnew\\b", "\\bdelete\\b"
    };

    for(const QString& pattern : keywordPatterns)
    {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    stringFormat.setForeground(QColor(0,128,0));
    HighlightingRule stringRule;
    stringRule.pattern = QRegularExpression("\".*\"");
    stringRule.format = stringFormat;
    highlightingRules.append(stringRule);

    numberFormat.setForeground(QColor(255,165,0));
    HighlightingRule numberRule;
    numberRule.pattern = QRegularExpression("\\b[0-9]+\\b");
    numberRule.format = numberFormat;
    highlightingRules.append(numberRule);

    preprocessorFormat.setForeground(QColor(128,0,128));
    HighlightingRule preprocessorRule;
    preprocessorRule.pattern = QRegularExpression("#[a-zA-z]+");
    preprocessorRule.format = preprocessorFormat;
    highlightingRules.append(preprocessorRule);

    commentFormat.setForeground(QColor(128,128,128)); 
    commentFormat.setFontItalic(true);

    HighlightingRule singleLineCommentRule;
    singleLineCommentRule.pattern = QRegularExpression("//[^\n]*");
    singleLineCommentRule.format = commentFormat;
    highlightingRules.append(singleLineCommentRule);

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");

}

void gui::SyntaxHighlighter::highlightBlock(const QString& text)
{
    for(const HighlightingRule& rule: highlightingRules)
    {
        QRegularExpressionMatchIterator it = rule.pattern.globalMatch(text);
        while(it.hasNext())
        {
            QRegularExpressionMatch match = it.next();
            setFormat(match.capturedStart(),match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);
    int startIndex = 0;
    if(previousBlockState() != 1)
    {
        startIndex = text.indexOf(commentStartExpression);
    }

    while(startIndex >= 0)
    {
        QRegularExpressionMatch endMatch = commentEndExpression.match(text, startIndex);
        int endIndex = endMatch.capturedStart();
        int commentLength = 0;
        if(endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex + endMatch.capturedLength();
        }
        setFormat(startIndex, commentLength, commentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }

}




