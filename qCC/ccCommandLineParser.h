#ifndef CC_COMMAND_LINE_PARSER_HEADER
#define CC_COMMAND_LINE_PARSER_HEADER

//qCC
#include "fileIO/FileIOFilter.h"

//qCC_db
#include <ccHObject.h>

//Qt
#include <QString>
#include <QStringList>

//STL
#include <vector>

class ccPointCloud;
class ccGenericMesh;
class ccProgressDialog;
class QDialog;

//! Command line parser
class ccCommandLineParser
{
public:
	static int Parse(int nargs, char** args);

protected:

	bool commandLoad						(QStringList& arguments);
	bool commandSubsample					(QStringList& arguments, ccProgressDialog* pDlg = 0);
	bool commandCurvature					(QStringList& arguments, QDialog* parent = 0);
	bool commandDensity						(QStringList& arguments, QDialog* parent = 0);
	bool commandApproxDensity				(QStringList& arguments, QDialog* parent = 0);
	bool commandSFGradient					(QStringList& arguments, QDialog* parent = 0);
	bool commandRoughness					(QStringList& arguments, QDialog* parent = 0);
	bool commandSampleMesh					(QStringList& arguments, ccProgressDialog* pDlg = 0);
	bool commandBundler						(QStringList& arguments);
	bool commandDist						(QStringList& arguments, bool cloud2meshDist, QDialog* parent = 0);
	bool commandFilterSFByValue				(QStringList& arguments);
	bool commandMergeClouds					(QStringList& arguments);
	bool commandStatTest					(QStringList& arguments, ccProgressDialog* pDlg = 0);
	bool commandBestFitPlane				(QStringList& arguments);
	bool matchBBCenters						(QStringList& arguments);
	bool commandICP							(QStringList& arguments, QDialog* parent = 0);
	bool commandChangeCloudOutputFormat		(QStringList& arguments);
	bool commandChangeMeshOutputFormat		(QStringList& arguments);

protected:

	//! Default constructor
	/** Shouldn't be called by user.
	**/
	ccCommandLineParser();

	//! Destructor
	/** Shouldn't be called by user.
	**/
	~ccCommandLineParser();

	//! Parses command line
	int parse(QStringList& arguments, bool silent, QDialog* parent = 0);

	//! Loaded entity description
	struct EntityDesc
	{
		QString basename;
		QString path;

		EntityDesc(QString filename);
		EntityDesc(QString basename, QString path);
		virtual ccHObject* getEntity() = 0;
	};

	//! Loaded cloud description
	struct CloudDesc : EntityDesc
	{
		ccPointCloud* pc;
		int indexInFile;

		CloudDesc()
			: EntityDesc(QString())
			, pc(0)
			, indexInFile(-1)
		{}

		CloudDesc(	ccPointCloud* cloud,
					QString filename,
					int index = -1)
			: EntityDesc(filename)
			, pc(cloud)
			, indexInFile(index)
		{}

		CloudDesc(	ccPointCloud* cloud,
					QString basename,
					QString path,
					int index = -1)
			: EntityDesc(basename,path)
			, pc(cloud)
			, indexInFile(index)
		{}
		
		virtual ccHObject* getEntity() { return (ccHObject*)pc; }
	};

	//! Loaded mesh description
	struct MeshDesc : EntityDesc
	{
		ccGenericMesh* mesh;

		MeshDesc()
			: EntityDesc(QString())
			, mesh(0)
		{}

		MeshDesc(	ccGenericMesh* _mesh,
					QString filename)
			: EntityDesc(filename)
			, mesh(_mesh)
		{}

		virtual ccHObject* getEntity() { return (ccHObject*)mesh; }
	};

	//! Exports a cloud or a mesh
	/** \return error string (if any)
	**/
	static QString Export(EntityDesc& cloudDesc, QString suffix = QString(), QString* outputFilename = 0);

	//! Reads out file format
	static CC_FILE_TYPES getFileFormat(QStringList& arguments);

    //! Removes all clouds
	void removeClouds();

    //! Removes all meshes
	void removeMeshes();

	//! Currently opened point clouds and their filename
	std::vector< CloudDesc > m_clouds;

	//! Currently opened meshes and their filename
	std::vector< MeshDesc > m_meshes;

	//! Mesh filename
	QString m_meshFilename;
};

#endif
