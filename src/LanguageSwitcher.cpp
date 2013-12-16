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

#include "LanguageSwitcher.h"

#include <QtGui>
#include "LabelClickable.h"

LanguageSwitcher::LanguageSwitcher( const QString & text, QWidget * parent )
	: QWidget( parent ), m_language( QLocale::AnyLanguage )
{
	createWidgets( text );
	setEnabled( m_checkBox->checkState() );
}

void
LanguageSwitcher::createWidgets( const QString & text )
{
	m_checkBox = new QCheckBox( text, this );
	connect( m_checkBox, SIGNAL( stateChanged( int ) ), SLOT( setEnabled( int ) ) );

	QHBoxLayout * layout = new QHBoxLayout( this );

	m_labelFlag = new LabelClickable( this );
	connect( m_labelFlag, SIGNAL( mouseClicked() ), SLOT( switchLanguage() ) );

	m_labelText = new LabelClickable( this );
	connect( m_labelText, SIGNAL( mouseClicked() ), SLOT( switchLanguage() ) );

	layout->setContentsMargins( 0, 0, 0, 0 );

	layout->addWidget( m_checkBox );
	layout->addWidget( m_labelFlag );
	layout->addWidget( m_labelText );
	layout->addStretch();
}

QLocale::Language
LanguageSwitcher::language() const
{
	return m_language;
}

void
LanguageSwitcher::setLanguage( QLocale::Language lang )
{
	if ( lang == m_language )
		return;

	m_language = lang;

	if ( lang == QLocale::Russian ) {
		m_labelFlag->setPixmap( QPixmap(":/ru-flag.png") );
		m_labelText->setText( "русский" );

	} else {
		m_labelFlag->setPixmap( QPixmap(":/en-flag.png") );
		m_labelText->setText( "english" );
	}
}

void
LanguageSwitcher::switchLanguage()
{
	if ( m_language == QLocale::Russian )
		setLanguage( QLocale::English );
	else
		setLanguage( QLocale::Russian );
}

void
LanguageSwitcher::setEnabled( int state )
{
	m_labelFlag->setEnabled( state == Qt::Checked );
	m_labelText->setEnabled( state == Qt::Checked );
}

bool
LanguageSwitcher::enabled() const
{
	return m_checkBox->checkState() == Qt::Checked;
}

void
LanguageSwitcher::setEnabled( bool check )
{
	m_checkBox->setCheckState( check ? Qt::Checked : Qt::Unchecked );
}


