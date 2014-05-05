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

#include "TextEdit.h"

#include <QtGui>

TextEdit::TextEdit( QWidget * parent, int rowFactor )
	: QTextEdit( parent ), m_rowFactor( rowFactor )
{
	setAttribute( Qt::WA_DeleteOnClose );

	printer.setPageMargins( 5, 5, 5, 5, QPrinter::Millimeter );

#ifndef Q_OS_WIN
	setFont( QFont("Droid Sans", 10 ) );
#endif
}

void
TextEdit::contextMenuEvent( QContextMenuEvent * event )
{
	QMenu * menu = createStandardContextMenu();

	QAction * actionPrint = menu->addAction( "Печатать..." );
	actionPrint->setShortcut( Qt::CTRL + Qt::Key_P );
	connect( actionPrint, SIGNAL( triggered() ), SLOT( printToPrinter() ) );

	QAction * actionToPdf = menu->addAction( "Сохранить в PDF..." );
	actionToPdf->setShortcut( Qt::CTRL + Qt::Key_E );
	connect( actionToPdf, SIGNAL( triggered() ), SLOT( saveToPdf() ) );

	menu->exec( event->globalPos() );

	delete actionToPdf;
	delete actionPrint;
	delete menu;
}
void
TextEdit::printToPrinter()
{
	QPrintDialog pd( &printer );

	if ( pd.exec() == QDialog::Accepted ) {

		printer.setOutputFormat( QPrinter::NativeFormat );
		print( &printer );
	}
}

void
TextEdit::saveToPdf()
{
	QSettings settings;

	QString fileName = QFileDialog::getSaveFileName( 0, "Сохранит в PDF",
			settings.value( DIR_PATH, ".").toString() +
			QDir::separator() + DefaultFileName,
			tr("PDF files (*.pdf)"));

	if ( ! fileName.isEmpty() ) {
		// save last saving dir
		QFileInfo fileInfo( fileName );

		settings.setValue( DIR_PATH, fileInfo.dir().path() );

		printer.setOutputFormat( QPrinter::PdfFormat );
		printer.setOutputFileName( fileName );
		print( &printer );
	}
}

void
TextEdit::setDefaultFileName( const QString & fileName )
{
	DefaultFileName = fileName;
}

QSize
TextEdit::sizeHint() const
{
	if ( m_rowFactor == -1 )
		return QTextEdit::sizeHint();

	QFontMetrics fm( font() );

	const int h = qMax( fm.height(), 14 ) * ( m_rowFactor + 1 );

	return QSize( 192, h );
}

