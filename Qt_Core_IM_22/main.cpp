#include <QtCore/QCoreApplication>

#include <qdebug.h>
#include <qfile.h>
#include <qdatetime.h>
#include <qtextstream.h>

const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);

void lhandler(QtMsgType type, const QMessageLogContext& context, const QString &msg) {
	// qDebug함수가 호출되면 여기가 먼저 호출된다.

	QString txt;
	switch (type) {
	case QtInfoMsg:
		txt = QString("Info: %1 in %2").arg(msg);
		break;
	case QtDebugMsg:
		txt = QString("Debug: %1 in %2").arg(msg);
		break;
	case QtWarningMsg:
		txt = QString("Warning: %1 in %2").arg(msg);
		break;
	case QtCriticalMsg:
		txt = QString("Critical: %1 in %2").arg(msg);
		break;
	case QtFatalMsg:
		txt = QString("Fatal: %1 in %2").arg(msg);
		break;
	}

	QFile file("log.txt");
	if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
		QTextStream ts(&file);
		ts << QDateTime::currentDateTime().toString() << " - " << txt << " file: " << context.file << " line: " << context.line << "\r\n";
		ts.flush();
		file.close();
	}

	(*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
	// 위 함수가 없으면 메시지출력이 안됨.
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	// Console창에 메시지를 전시하는 정도는 알지만 아래의 명령이 어떤 차이가 있는지는 모른다.
	
	qInstallMessageHandler(lhandler);

	qInfo() << "This is a info messages";
	qDebug() << "This is a debug messages";
	qWarning() << "This is a Warning messages";
	qCritical() << "This is a critical messages";

	// qFatal("THIS IS SPARTA!!!");
	// qFatal : 어플리케이션을 죽인다.

	return a.exec();
}
