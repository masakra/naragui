/***************************************************************************
 *   Copyright (C) 2011 by Sergey N Chursanov                              *
 *                                                                         *
 *   email: masakra@mail.ru                                                *
 *   jabber: masakra@jabber.ru                                             *
 *                                                                         *
 *   All comments, if not ascii, in koi8-r                                 *
 *                                                                         *
 *   Permission is hereby granted, free of charge, to any person obtaining *
 *   a copy of this software and associated documentation files (the       *
 *   "Software"), to deal in the Software without restriction, including   *
 *   without limitation the rights to use, copy, modify, merge, publish,   *
 *   distribute, sublicense, and/or sell copies of the Software, and to    *
 *   permit persons to whom the Software is furnished to do so, subject to *
 *   the following conditions:                                             *
 *                                                                         *
 *   The above copyright notice and this permission notice shall be        *
 *   included in all copies or substantial portions of the Software.       *
 *                                                                         *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       *
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    *
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. *
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR     *
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR *
 *   OTHER DEALINGS IN THE SOFTWARE.                                       *
 ***************************************************************************/

 /** \class TextEdit
 //
 // \brief Предок всех печатных документов
 */

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

#include <QPrinter>

#define DIR_PATH "save_to_pdf_dir_path"

class TextEdit : public QTextEdit
{
	Q_OBJECT

	private:
		QPrinter printer;

		QString DefaultFileName;

		int m_rowFactor;    ///< делает виджет высотой для \a m_rowFactor строк

	protected:
		virtual void contextMenuEvent( QContextMenuEvent * event );

	public:
		TextEdit( QWidget * parent, int rowFactor = -1 );

		void setDefaultFileName( const QString & fileName );

		virtual QSize sizeHint() const;

	public Q_SLOTS:
		void printToPrinter();
		void saveToPdf();
};

#endif


