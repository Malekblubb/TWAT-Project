/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <core/client/client.h>

#include <core/shared/twmapextract.h>

#include <core/tools/tw/datafiles/map.h>

#include <QFileDialog>
#include <QMessageBox>


CUiExtractImages::CUiExtractImages(MainWindow *window) :
	m_mainWindow(window),
	m_scene(new QGraphicsScene)
{
	connect(this, SIGNAL(Load()), this, SLOT(OnLoad()));
	connect(this, SIGNAL(Save(int)), this, SLOT(OnSave(int)));
}

CUiExtractImages::~CUiExtractImages()
{
	delete m_scene;
}

void CUiExtractImages::OnLoadClicked()
{
	emit Load();
}

void CUiExtractImages::OnBrowseClicked()
{
	m_mainWindow->m_ui->m_leExtImgMapPath->setText(QFileDialog::getOpenFileName(
										 m_mainWindow,
										 "Open Map File",
										 "/home",
										 "Teeworlds Map File (*.map)"));
	emit Load();
}

void CUiExtractImages::OnListEntryClicked(const QModelIndex &index)
{
	if(m_mainWindow->m_ui->m_lwExtImgImages->item(index.row())->isSelected())
	{
		m_scene->clear();

		QImage img(m_mainWindow->Client()->TwMapExtract()->ImageAt(index.row())->Data(),
				   m_mainWindow->Client()->TwMapExtract()->ImageAt(index.row())->Width(),
				   m_mainWindow->Client()->TwMapExtract()->ImageAt(index.row())->Height(),
				   QImage::Format_ARGB32);

		m_scene->addPixmap(QPixmap::fromImage(img.rgbSwapped()));
		m_mainWindow->m_ui->m_gvExtImgPreview->setScene(m_scene);
	}
}

void CUiExtractImages::OnSaveSelectedClicked()
{
	emit Save(SELECTED);
}

void CUiExtractImages::OnSaveAllClicked()
{
	emit Save(ALL);
}

void CUiExtractImages::OnLoad()
{
	m_mapPath = m_mainWindow->m_ui->m_leExtImgMapPath->text();

	// load the map
	if((!m_mapPath.isEmpty()) && (m_mapPath != ""))
		m_mainWindow->Client()->TwMapExtract()->Load(m_mapPath.toStdString());

	// refresh the ui
	this->RefreshUiInfos();
}

void CUiExtractImages::OnSave(int mode)
{
	if(m_mainWindow->m_ui->m_lwExtImgImages->count() > 0)
	{
		QFileDialog saveDialog;
		QString saveDirPath;
		saveDialog.setOption(QFileDialog::ShowDirsOnly);
		saveDialog.setFileMode(QFileDialog::Directory);

		if(saveDialog.exec())
			saveDirPath = saveDialog.directory().path();


		if(!saveDirPath.isEmpty())
		{
			QString path;


			if(mode == ALL)
			{
				for(int i = 0; i < m_mainWindow->m_ui->m_lwExtImgImages->count(); ++i)
				{
					path = saveDirPath + "/" + m_mainWindow->Client()->TwMapExtract()->ImageAt(i)->Name().c_str() + ".png";
					QFile file(path);

					if(file.exists())
					{
						if(QMessageBox::question(m_mainWindow, "File already exists",
												 "A file with the name \"" + QString(m_mainWindow->Client()->TwMapExtract()->ImageAt(i)->Name().c_str()) + "\" already exists in this directory.\nDo you want to overwrite it?",
												 QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
							continue;
					}

					m_mainWindow->Client()->TwMapExtract()->Save(i, path.toStdString());
				}
			}
			if(mode == SELECTED)
			{
				if(m_mainWindow->m_ui->m_lwExtImgImages->selectedItems().size() > 0)
				{
					for(int i = 0; i < m_mainWindow->m_ui->m_lwExtImgImages->count(); ++i)
					{
						if(m_mainWindow->m_ui->m_lwExtImgImages->item(i)->isSelected())
						{
							path = saveDirPath + "/" + m_mainWindow->Client()->TwMapExtract()->ImageAt(i)->Name().c_str() + ".png";
							QFile file(path);

							if(file.exists())
							{
								if(QMessageBox::question(m_mainWindow, "File already exists",
														 "A file with the name \"" + QString(m_mainWindow->Client()->TwMapExtract()->ImageAt(i)->Name().c_str()) + "\" already exists in this directory.\nDo you want to overwrite it?",
														 QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
									continue;
							}

							m_mainWindow->Client()->TwMapExtract()->Save(i, path.toStdString());
						}
					}
				}
				else
					QMessageBox::critical(m_mainWindow, "Error", "No image(s) selected");
			}
		}
	}
	else
		QMessageBox::critical(m_mainWindow, "Error", "No map loaded");
}

void CUiExtractImages::RefreshUiInfos()
{
	m_mainWindow->m_ui->m_lbExtImgNumImagesVar->setText(QString::number(m_mainWindow->Client()->TwMapExtract()->NumImages()));

	m_mainWindow->m_ui->m_lwExtImgImages->clear();
	for(int i = 0; i < m_mainWindow->Client()->TwMapExtract()->NumImages(); ++i)
		m_mainWindow->m_ui->m_lwExtImgImages->addItem(m_mainWindow->Client()->TwMapExtract()->ImageAt(i)->Name().c_str());
}
