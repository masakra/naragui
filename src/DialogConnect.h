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

/** \class DialogConnect
 *
 * \brief Диалог соединения с базой данных
 */

#ifndef DIALOGCONNECT_H
#define DIALOGCONNECT_H

#include <QDialog>

class QGroupBox;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QPushButton;
class QSqlDatabase;

class DialogConnect : public QDialog
{
	Q_OBJECT

	private:
		QString m_driver;

		QLabel * m_labelBanner;

		QGroupBox * m_groupServer;

		QLineEdit * m_editUsername,
				  * m_editPassword,
				  * m_editHost,
				  * m_editPort,
				  * m_editDatabase;

		QPushButton	* m_buttonOk,
					* m_buttonServer;

		QLabel * m_labelHint;

		void setLabelHint();

		void createWidgets();
		QHBoxLayout * createLabeledEdit( QLineEdit ** edit,
				const QString & labelText );
		void loadSettings();

		QTextCodec * m_codec;

		/*! \fn QString u2u( const char * uft8 ) const
		 *
		 * \brief UTF-8 const char * string to unicode
		 */
		QString u2u( const char * utf8 ) const;

		QSqlDatabase * m_db;

		void init( const QString & title );

	private slots:
		void doConnect();
		void check();

	protected:
		void showEvent( QShowEvent * event );

	public:
		DialogConnect( const QString & title, const QString & driver,
				QWidget * parent = 0 );

		/*! \fn DialogConnect( const QString & title, QSqlDatabase * db, QWidget * parent = 0 )
		 *
		 * Вариант конструктора для имеющегося экземпляра QSqlDatabase. Не создаёт подключения к
		 * базе данных. Заполняет поля в \a db для подключения
		 */
		DialogConnect( const QString & title, QSqlDatabase * db, QWidget * parent = 0 );

		void setBanner( const QPixmap & pixmap );

		void saveSettings();

		QString hostName() const;

		QString port() const;

		QString databaseName() const;

		QString userName() const;

		QString password() const;
};

#endif

