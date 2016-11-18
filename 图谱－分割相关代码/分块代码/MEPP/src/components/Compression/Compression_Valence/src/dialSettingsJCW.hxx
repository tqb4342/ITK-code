#ifndef HEADER_MEPP_COMPONENT_VALENCE_PLUGIN_SETTINGS_JCW_H
#define HEADER_MEPP_COMPONENT_VALENCE_PLUGIN_SETTINGS_JCW_H

#include <mepp_config.h>
#ifdef BUILD_component_Compression_Valence

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wuninitialized"
#endif
#include <QtGui>
#ifndef _MSC_VER
#pragma GCC diagnostic warning "-Wuninitialized"
#endif

#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif

#include "ui_dialSettingsJCW.h"

/**
 \class	SettingsDialogJCW

 \brief	Settings dialog JCW. 

 */

class SettingsDialogJCW : public QDialog, public Ui_SettingsJCW
{
    Q_OBJECT

public:

    /**
     \fn	SettingsDialogJCW::SettingsDialogJCW(QWidget *parent = 0);
    
     \brief	Constructor.
    
    
     \param [in,out]	parent	If non-null, the parent.
     */

    SettingsDialogJCW(QWidget *parent, QString &saveLocation);

    /**
     \fn	void SettingsDialogJCW::accept();
    
     \brief	Accepts this object.
    
     */

    void accept();

private slots:

    /**
     \fn	void SettingsDialogJCW::loadDefaults();
    
     \brief	Loads the defaults.
    
     */

    void loadDefaults();

    /**
     \fn	void SettingsDialogJCW::loadFromSettings();
    
     \brief	Loads from settings.
    
     */

    void loadFromSettings();

    /**
     \fn	void SettingsDialogJCW::saveToSettings();
    
     \brief	Saves to settings.
    
     */

    void saveToSettings();

	/**
	 \fn	void SettingsDialogJCW::setFilename();
	
	 \brief	Sets the filename.

	 */

	void setFilename();

private:
	QString &saveLocation_;
};

#endif

#endif // HEADER_MEPP_COMPONENT_VALENCE_PLUGIN_SETTINGS_COMP_H