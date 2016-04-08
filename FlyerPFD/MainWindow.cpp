/***************************************************************************//**
 * @file example/MainWindow.cpp
 * @author  Marek M. Cel    <marekcel@marekcel.pl>
 *          Peter Zhang     <mbyzhang@outlook.com>
 *
 * @section LICENSE
 *
 * Copyright (C) 2013 Marek M. Cel
 *
 * This file is part of FlyerProject / QFI. You can redistribute and modify it
 * under the terms of GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Further information about the GNU General Public License can also be found
 * on the world wide web at http://www.gnu.org.
 *
 * ---
 *
 * Copyright (C) 2013 Marek M. Cel & 2015 Peter Zhang
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef MAINWINDOW_CPP
#define MAINWINDOW_CPP
#endif

////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <math.h>
#include <string>

#include "MainWindow.h"
#include "ui_MainWindow.h"

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) {
    m_ui = new Ui::MainWindow;
    m_isFinished = true;
    m_manager = new QNetworkAccessManager(this);
    m_ui->setupUi( this );
    m_timerId = startTimer( 40 );
    m_time.start();
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    if ( m_timerId ) killTimer( m_timerId );

    if ( m_ui ) delete m_ui; m_ui = 0;
}

////////////////////////////////////////////////////////////////////////////////


void MainWindow::replyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        QJsonParseError jsonError;
        QJsonDocument json = QJsonDocument::fromJson(data, &jsonError);
        if (jsonError.error == QJsonParseError::NoError) {
            if (json.isObject()) {
                QJsonObject obj = json.object();
                if (obj.contains(("flyerData"))) {

                    float beta      = (obj["beta"].toDouble() - 512.0) / 64.0;      // ?
                    float alpha     = (obj["alpha"].toDouble() - 512.0) / 64.0;       // ?
                    float roll      = obj["roll"].toDouble();       // deg
                    float pitch     = obj["pitch"].toDouble();      // deg
                    float slipSkid  = (obj["slipSkid"].toDouble() - 128.0) / 64.0;   // -
                    float turnRate  = obj["turnRate"].toDouble();   // deg/s
                    float devH      = obj["devH"].toDouble();       // -
                    float devV      = obj["devV"].toDouble();       // -
                    float heading   = obj["heading"].toDouble();    // deg
                    float airspeed  = obj["airspeed"].toDouble();   // kts
                    float machNo    = obj["machNo"].toDouble();     // -
                    float altitude  = obj["altitude"].toDouble();   // ft
                    float pressure  = obj["pressure"].toDouble();   // inHg
                    float climbRate = obj["climbRate"].toDouble();  // ft/min
                    m_ui->widgetPFD->setFlightPathMarker ( alpha, beta );
                    m_ui->widgetPFD->setRoll          ( roll     );
                    m_ui->widgetPFD->setPitch         ( pitch     );
                    m_ui->widgetPFD->setSlipSkid      ( slipSkid  );
                    m_ui->widgetPFD->setTurnRate      ( turnRate / 6.0f );
                    m_ui->widgetPFD->setDevH          ( devH      );
                    m_ui->widgetPFD->setDevV          ( devV      );
                    m_ui->widgetPFD->setHeading       ( heading   );
                    m_ui->widgetPFD->setAirspeed      ( airspeed  );
                    m_ui->widgetPFD->setMachNo        ( machNo    );
                    m_ui->widgetPFD->setAltitude      ( altitude  );
                    m_ui->widgetPFD->setPressure      ( pressure  );
                    m_ui->widgetPFD->setClimbRate     ( climbRate / 100.0f );

                    m_ui->widgetPFD->update();

                }
            }

        }
        else {
            cout << "[QJsonParseError] E: " << jsonError.errorString().toStdString() << endl;
        }
    }
    else {
        cout << "[NetworkReply] E: " << reply->errorString().toStdString() << endl;
    }

    reply->deleteLater();
    m_isFinished = true;
}




void MainWindow::timerEvent( QTimerEvent *event )
{
    /////////////////////////////////
    QMainWindow::timerEvent( event );
    /////////////////////////////////
    if (!m_isFinished) return;
    m_isFinished = false;
    m_manager->get(QNetworkRequest(QUrl("http://localhost:10005")));

}
