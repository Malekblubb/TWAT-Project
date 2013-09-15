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


CUiExtractImages::CUiExtractImages(Ui::MainWindow *ui, MainWindow *window) :
	m_ui(ui),
	m_mainWindow(window)
{
	connect(this, SIGNAL(Load()), this, SLOT(OnLoad()));
	connect(this, SIGNAL(Save(int)), this, SLOT(OnSave(int)));
}

void CUiExtractImages::OnLoadClicked()
{
	emit Load();
}

void CUiExtractImages::OnBrowseClicked()
{
	m_ui->m_leExtImgMapPath->setText(QFileDialog::getOpenFileName(
										 m_mainWindow,
										 "Open Map File",
										 "/home",
										 "Teeworlds Map File (*.map)"));
	emit Load();
}

void CUiExtractImages::OnListEntryClicked(const QModelIndex &index)
{
	if(m_ui->m_lwExtImgImages->item(index.row())->isSelected())
	{
		QGraphicsScene *scene = new QGraphicsScene();

		QImage img((uchar*)m_mainWindow->Client()->TwMapExtract()->ImageAt(index.row())->Data(),
				   m_mainWindow->Client()->TwMapExtract()->ImageAt(index.row())->Width(),
				   m_mainWindow->Client()->TwMapExtract()->ImageAt(index.row())->Height(),
				   QImage::Format_ARGB32);

		scene->addPixmap(QPixmap::fromImage(img.rgbSwapped()));
		m_ui->m_gvExtImgPreview->setScene(scene);
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
	m_mapPath = m_ui->m_leExtImgMapPath->text();

	// load the map
	if((!m_mapPath.isEmpty()) && (m_mapPath != ""))
		m_mainWindow->Client()->TwMapExtract()->Load(m_mapPath.toStdString());

	// refresh the ui
	this->RefreshUiInfos();
}

void CUiExtractImages::OnSave(int mode)
{
	if(m_ui->m_lwExtImgImages->count() > 0)
	{
		QFileDialog saveDialog;
		QString saveDirPath;
		saveDialog.setOption(QFileDialog::ShowDirsOnly);
		saveDialog.setFileMode(QFileDialog::Directory);

		if(saveDialog.exec())
			saveDirPath = saveDialog.directory().path();


		if(!saveDirPath.isEmpty())
		{
			if(mode == ALL)
			{
				for(int i = 0; i < m_ui->m_lwExtImgImages->count(); ++i)
				{
					QString path = saveDirPath + "/" + m_mainWindow->Client()->TwMapExtract()->ImageAt(i)->Name().c_str() + ".png";
					m_mainWindow->Client()->TwMapExtract()->Save(i, path.toStdString());
				}
			}
			if(mode == SELECTED)
			{
				if(m_ui->m_lwExtImgImages->selectedItems().size() > 0)
				{
					for(int i = 0; i < m_ui->m_lwExtImgImages->count(); ++i)
					{
						if(m_ui->m_lwExtImgImages->item(i)->isSelected())
						{
							QString path = saveDirPath + "/" + m_mainWindow->Client()->TwMapExtract()->ImageAt(i)->Name().c_str() + ".png";
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
	m_ui->m_lbExtImgNumImagesVar->setText(QString::number(m_mainWindow->Client()->TwMapExtract()->NumImages()));

	m_ui->m_lwExtImgImages->clear();
	for(int i = 0; i < m_mainWindow->Client()->TwMapExtract()->NumImages(); ++i)
		m_ui->m_lwExtImgImages->addItem(m_mainWindow->Client()->TwMapExtract()->ImageAt(i)->Name().c_str());
}
