// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef ITKGDCMIMAGEDATAREADER_H
#define ITKGDCMIMAGEDATAREADER_H

#include <dtkCore/dtkAbstractDataReader.h>

#include "itkDataImageReaderPluginExport.h"


#include "gdcmScanner.h"

#include <sstream>
#include <vector>
#include <string>

class itkGDCMDataImageReaderPrivate;

namespace itk
{
  class SliceReadCommand;
}

class ITKDATAIMAGEREADERPLUGIN_EXPORT itkGDCMDataImageReader : public dtkAbstractDataReader
{
  Q_OBJECT

    public:

  typedef std::vector<std::string> FileList;
  typedef std::map<std::string, FileList> FileListMapType;
  
  itkGDCMDataImageReader(void);
  virtual ~itkGDCMDataImageReader(void);

  virtual QString description(void) const;

  virtual QStringList handled(void) const;
  static bool registered(void);

  friend class itk::SliceReadCommand;
    
  public slots:
  bool canRead (QString path);
  bool canRead (QStringList paths);

  void readInformation (QString path);
  void readInformation (QStringList paths);
    
  bool read (QString path);
  bool read (QStringList paths);

 private:

  template <typename type, unsigned int dimension> inline void CreateReader (FileList filelist, itk::ImageIOBase io, itk::ProcessObject::Pointer reader)
  {
    itk::ImageSeriesReader<itk::Image<type, dimension > >::Pointer imagereader = itk::ImageFileReader<itk::Image<unsigned char, dimension > >::New(); 
    imagereader->UseStreamingOn();
    imagereader->SetImageIO ( io );
    imagereader->SetFileNames ( filelist );
    reader = imagereader;
  }

  FileListMapType Sort (FileList list);
  FileList UnfoldMap (FileListMapType map);
  
  itkGDCMDataImageReaderPrivate *d;
  gdcm::Scanner m_Scanner;
  
};

dtkAbstractDataReader *createItkGDCMDataImageReader(void);

#endif
