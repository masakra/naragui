/*
 * Copyright (C) 2013  Sergey N Chursanov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 * --------------------------------------------------------------------- */

#include "DialogConnect.h"

#include <QtGui>
#include <QtSql>
#include <NaraPg>

DialogConnect::DialogConnect( const QString & title, const QString & driver,
		QWidget * parent )
	: QDialog( parent ), m_driver( driver ),
	m_codec( QTextCodec::codecForName("UTF-8") ), m_db( 0 )
{
	init( title );
}

DialogConnect::DialogConnect( const QString & title, QSqlDatabase * db, QWidget * parent )
	: QDialog( parent ), m_codec( QTextCodec::codecForName("UTF-8") ), m_db( db )
{
	init( title );
}

void
DialogConnect::init( const QString & title )
{
	setWindowTitle( title );
	setWindowIcon( QIcon::fromTheme("network-server",
				QIcon(":/server-database.png") ) );
	createWidgets();
	loadSettings();
	check();
}

void
DialogConnect::createWidgets()
{
	// картинка

	m_labelBanner = new QLabel( this );

	// группа User

	QGroupBox * groupUser = new QGroupBox( u2u("Пользователь") );
	QGridLayout * layoutUser = new QGridLayout( groupUser );
	createLabeledEdit( &m_editUsername, u2u("&Пользователь"), layoutUser, 0 );
	createLabeledEdit( &m_editPassword, u2u("П&ароль"), layoutUser, 1 );
	m_editPassword->setEchoMode( QLineEdit::Password );

	connect( m_editUsername, SIGNAL( textChanged( const QString ) ),
			SLOT( check() ) );

	// группа Server

	m_labelHint = new QLabel( this );
	m_labelHint->setEnabled( false );

	m_groupServer = new QGroupBox( u2u("Сервер") );
	QGridLayout * layoutServer = new QGridLayout( m_groupServer );

	createLabeledEdit( &m_editHost, u2u("&Сервер"), layoutServer, 0 );
	createLabeledEdit( &m_editPort, u2u("П&орт"), layoutServer, 1 );
	createLabeledEdit( &m_editDatabase, u2u("База &данных"), layoutServer, 2 );
	m_groupServer->hide(); // при запуске не показывать

	connect( m_editHost, SIGNAL( textChanged( const QString & ) ),
			SLOT( check() ) );
	connect( m_editPort, SIGNAL( textChanged( const QString & ) ),
			SLOT( check() ) );
	connect( m_editDatabase, SIGNAL( textChanged( const QString & ) ),
			SLOT( check() ) );

	QVBoxLayout * layoutButtons = new QVBoxLayout();
	m_buttonOk = new QPushButton( u2u("Ok") );
	connect( m_buttonOk, SIGNAL( clicked() ), m_db ? SLOT( accept() ) : SLOT( doConnect() ) );

	QPushButton * buttonClose = new QPushButton( u2u("Закрыть") );
	connect( buttonClose, SIGNAL( clicked() ), SLOT( close() ) );

	m_buttonServer = new QPushButton( u2u("Сервер") );
	m_buttonServer->setCheckable( true );
	connect( m_buttonServer, SIGNAL( toggled( bool ) ), m_groupServer,
			SLOT( setVisible( bool ) ) );
	connect( m_buttonServer, SIGNAL( toggled( bool ) ), m_labelHint,
			SLOT( setHidden( bool ) ) );


	layoutButtons->addWidget( m_buttonOk );
	layoutButtons->addWidget( buttonClose );
	layoutButtons->addWidget( m_buttonServer );

	QGridLayout * layoutMain = new QGridLayout( this );
	layoutMain->setSizeConstraint( QLayout::SetFixedSize );
	layoutMain->setContentsMargins( 5, 3, 5, 5 );
	layoutMain->setSpacing( 5 );

	layoutMain->addWidget( m_labelBanner, 0, 0, 1, 2 );
	layoutMain->addWidget( groupUser, 1, 0 );
	layoutMain->addWidget( m_groupServer, 2, 0 );
	layoutMain->addLayout( layoutButtons, 1, 1 );
	layoutMain->addWidget( m_labelHint, 3, 0 );
}

void
DialogConnect::loadSettings()
{
	QString port;

	if ( m_driver == "QPSQL" )
		port = "5432";
	else if ( m_driver == "QMYSQL" )
		port = "3306";
	else
		port.clear();

	QSettings ini;
	ini.beginGroup( "login" );
		m_editUsername->setText( ini.value("user").toString() );
	ini.endGroup();
	ini.beginGroup( "server" );
		m_editHost->setText( ini.value( "host", "localhost" ).toString() );
		m_editPort->setText( ini.value( "port", port ).toString() );
		m_editDatabase->setText( ini.value("database").toString() );
	ini.endGroup();

	setLabelHint();

	// если имя не пустое - фокус ввода на пароль
	if ( ! m_editUsername->text().isEmpty() )
		m_editPassword->setFocus();

	// если хотя бы один параметр соединения пустой, показать группу, спрятать метку
	if ( m_editHost->text().isEmpty() || m_editPort->text().isEmpty() ||
			m_editDatabase->text().isEmpty() ) {
		m_buttonServer->setChecked( true );
		//groupServer->show();
		//labelHint->hide();
	}
}

void
DialogConnect::saveSettings()
{
	QSettings ini;
	ini.beginGroup( "login" );
		ini.setValue( "user", m_editUsername->text() );
	ini.endGroup();
	ini.beginGroup( "server" );
		ini.setValue( "host", m_editHost->text() );
		ini.setValue( "port", m_editPort->text() );
		ini.setValue( "database", m_editDatabase->text() );
	ini.endGroup();
}

void
DialogConnect::doConnect()
{
	if( PgSchema::connect( m_editHost->text(), m_editPort->text(), m_editDatabase->text(),
			m_editUsername->text(), m_editPassword->text(), qApp->applicationName(),
			qApp->applicationVersion() ) ) {
		saveSettings();
		accept();
	} else
		QMessageBox::critical( this, "Error", PgSchema::lastDbError() );
}

void
DialogConnect::createLabeledEdit( QLineEdit ** edit, const QString & labelText, QGridLayout * gridLayout, int row )
{
	( *edit ) = new QLineEdit( this );

	QLabel * label = new QLabel( labelText, this );

	label->setBuddy( *edit );

	gridLayout->addWidget( label, row, 0, Qt::AlignRight );
	gridLayout->addWidget( *edit, row, 1 );
}

void
DialogConnect::check()
{
	m_buttonOk->setEnabled( ! m_editUsername->text().isEmpty() &&
			! m_editHost->text().isEmpty() &&
			! m_editPort->text().isEmpty() &&
			! m_editDatabase->text().isEmpty() );

	setLabelHint();
}

void
DialogConnect::setLabelHint()
{
	m_labelHint->setText( m_editHost->text() + " " +
			m_editPort->text() + " " +
			m_editDatabase->text() );
}

QString
DialogConnect::u2u( const char * utf8 ) const
{
	return m_codec->toUnicode( utf8 );
}

void
DialogConnect::setBanner( const QPixmap & pixmap )
{
	m_labelBanner->setPixmap( pixmap );
}

void
DialogConnect::showEvent( QShowEvent * event )
{
	QDialog::showEvent( event );

	// move to desktop center

	QRect desktop = qApp->desktop()->screenGeometry();

	move( ( desktop.width() - width() ) / 2,
			( desktop.height() - height() ) / 2 );
}

QString
DialogConnect::hostName() const
{
	return m_editHost->text();
}

QString
DialogConnect::port() const
{
	return m_editPort->text();
}

QString
DialogConnect::databaseName() const
{
	return m_editDatabase->text();
}

QString
DialogConnect::userName() const
{
	return m_editUsername->text();
}

QString
DialogConnect::password() const
{
	return m_editPassword->text();
}

