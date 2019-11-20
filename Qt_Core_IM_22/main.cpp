#include <QtCore/QCoreApplication>

#include <qdebug.h>
#include <qfile.h>
#include <qdatetime.h>
#include <qtextstream.h>

const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);

void lhandler(QtMsgType type, const QMessageLogContext& context, const QString &msg) {
	// qDebug�Լ��� ȣ��Ǹ� ���Ⱑ ���� ȣ��ȴ�.

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
	// �� �Լ��� ������ �޽�������� �ȵ�.
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	// Consoleâ�� �޽����� �����ϴ� ������ ������ �Ʒ��� ����� � ���̰� �ִ����� �𸥴�.
	
	qInstallMessageHandler(lhandler);

	qInfo() << "This is a info messages";
	qDebug() << "This is a debug messages";
	qWarning() << "This is a Warning messages";
	qCritical() << "This is a critical messages";

	// qFatal("THIS IS SPARTA!!!");
	// qFatal : ���ø����̼��� ���δ�.

	return a.exec();
}
