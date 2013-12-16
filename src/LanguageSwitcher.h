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

 /** \class LanguageSwitcher
  *
  * \brief Переключатель рус <-> eng
  */

#ifndef LANGUAGESWITCHER_H
#define LANGUAGESWITCHER_H

#include <QLocale>
#include <QWidget>

class QCheckBox;
class QLabel;
class LabelClickable;

class LanguageSwitcher : public QWidget
{
	Q_OBJECT

	private:
		void createWidgets( const QString & text );

		QCheckBox * m_checkBox;

		LabelClickable * m_labelFlag,
					   * m_labelText;

		QLocale::Language m_language;

	private Q_SLOTS:
		void switchLanguage();
		void setEnabled( int state );

	public:
		LanguageSwitcher( const QString & text, QWidget * parent = 0 );

		QLocale::Language language() const;

		void setLanguage( QLocale::Language lang );

		bool enabled() const;

		void setEnabled( bool check );
};

#endif


