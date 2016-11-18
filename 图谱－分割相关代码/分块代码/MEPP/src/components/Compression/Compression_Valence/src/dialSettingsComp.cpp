#include <mepp_config.h>
#ifdef BUILD_component_Compression_Valence

#include <QDir>

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wuninitialized"
#endif
#include <QFileDialog>
#include <QMessageBox>
#ifndef _MSC_VER
#pragma GCC diagnostic warning "-Wuninitialized"
#endif

#include "dialSettingsComp.hxx"

SettingsDialogComp::SettingsDialogComp(QWidget *parent, QString &saveLocation)
    : QDialog(parent), saveLocation_(saveLocation)
{
    setupUi(this);

	connect(pushButtonBrowse, SIGNAL(clicked()), this, SLOT(setFilename()));

    loadDefaults();
    loadFromSettings();
}

void SettingsDialogComp::loadDefaults()
{
}

void SettingsDialogComp::loadFromSettings()
{
}

void SettingsDialogComp::saveToSettings()
{
}

void SettingsDialogComp::accept()
{
    saveToSettings();

	if (!file_name->text().isEmpty())
		QDialog::accept();
	else
		QMessageBox::information(this, APPLICATION, tr("You must specify a filename."));
}

void SettingsDialogComp::setFilename()
{
	QString suffix;
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save P3D File - from Valence"),
											 saveLocation_, //QDir::currentPath(), //QString()
											 tr("P3D files (*.p3d)"), &suffix);
	if (!fileName.isEmpty())
	{
#ifdef __linux__
		if (suffix.indexOf(".p3d") >= 0)
			fileName += ".p3d";
#endif
		saveLocation_ = QFileInfo(fileName).absolutePath();

		file_name->setText(fileName);
	}
}

#endif