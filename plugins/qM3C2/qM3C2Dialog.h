//##########################################################################
//#                                                                        #
//#                       CLOUDCOMPARE PLUGIN: qM3C2                       #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 or later of the License.      #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#            COPYRIGHT: UNIVERSITE EUROPEENNE DE BRETAGNE                #
//#                                                                        #
//##########################################################################

#ifndef Q_M3C2_DIALOG_HEADER
#define Q_M3C2_DIALOG_HEADER

#include <ui_qM3C2Dialog.h>

//Local
#include <qM3C2Tools.h>

//Qt
#include <QSettings>

class ccMainAppInterface;
class ccPointCloud;

//! M3C2 plugin's main dialog
class qM3C2Dialog : public QDialog, public Ui::M3C2Dialog
{
	Q_OBJECT

public:

	//! Default constructor
	qM3C2Dialog(ccPointCloud* cloud1, ccPointCloud* cloud2, ccMainAppInterface* app);

	//! Returns cloud #1
	ccPointCloud* getCloud1() { return m_cloud1; }
	//! Returns cloud #2
	ccPointCloud* getCloud2() { return m_cloud2; }

	//! Get core points cloud (if any)
	/** Returns either cloud #1 or the cloud specified in the combo box.
		It can also return a null pointer if the user has requested
		sub-sampling.
	**/
	ccPointCloud* getCorePointsCloud();

	//! Returns the cloud to be used for normals orientation (if any)
	ccPointCloud* getNormalsOrientationCloud();

	//! Returns selected normals computation mode
	qM3C2Normals::ComputationMode getNormalsComputationMode() const;

	//! Returns the minimum number of points to compute stats (confidence mainly)
	unsigned getMinPointsForStats(unsigned defaultValue = 5) const;

	//! Exportation options
	enum ExportOptions {	PROJECT_ON_CLOUD1,
							PROJECT_ON_CLOUD2,
							PROJECT_ON_CORE_POINTS,
	};

	//! Returns selected export option
	ExportOptions getExportOption() const;

	//! Returns whether the original cloud should be kept instead of creating a new output one
	/** Only valid if the export option is PROJECT_ON_CORE_POINTS.
	**/
	bool keepOriginalCloud() const;

	//! Returns the max number of threads to use
	int getMaxThreadCount() const;

	//! Loads parameters from persistent settings
	void loadParamsFromPersistentSettings();
	//! Saves parameters to persistent settings
	void saveParamsToPersistentSettings();

protected slots:

	void swapClouds();
	void setCloud1Visibility(bool);
	void setCloud2Visibility(bool);
	void ifUseOtherCloudForCorePoints(bool);
	void saveParamsToFile();
	void loadParamsFromFile();
	void guessParamsSlow() { guessParams(false); }
	void projDestIndexChanged(int);

protected:

	//! Guess parameters from the cloud #1
	void guessParams(bool fastMode);

	//! Sets clouds
	void setClouds(ccPointCloud* cloud1, ccPointCloud* cloud2);

	//! Load parameters from QSettings
	void loadParamsFrom(const QSettings& settings);
	//! Saves parameters to QSettings
	void saveParamsTo(QSettings& settings);

	ccMainAppInterface* m_app;

	ccPointCloud* m_cloud1;
	ccPointCloud* m_cloud2;

	bool m_firstTimeInit;
};

#endif //Q_M3C2_DIALOG_HEADER