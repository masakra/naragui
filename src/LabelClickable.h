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

 /** \class LabelClickable
  *
  * \brief QLabel реагирующий на нажатие мыши
  */

#ifndef LABELCLICKABLE_H
#define LABELCLICKABLE_H

#include <QLabel>

class LabelClickable : public QLabel
{
	Q_OBJECT
	protected:
		virtual void mousePressEvent( QMouseEvent * e );

	public:
		LabelClickable( QWidget * parent = 0 );

	Q_SIGNALS:
		void mouseClicked();

};

#endif

