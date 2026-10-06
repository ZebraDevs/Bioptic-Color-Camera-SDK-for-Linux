/*
 * DemoGenerateConfiguration.cpp
 *
 *  Created on: Nov 18, 2019
 *  ©2022 Zebra Technologies Corp. and/or its affiliates.  All rights reserved.
 */


#include "ZebraCameraDemoMain.h"

#include <iostream>
#include <sstream>


void ZebraCameraDemoFrame::OnGenerateConfigClick(wxCommandEvent& event)
{

	(void)event;

	auto camera = GetCamera();
	if (camera)
	{
		std::string camera_config;

		try
		{
			camera_config = camera_manager_client_->RetrieveConfiguration(camera);
		}
		catch (std::exception& e)
		{
			wxString msg;
			msg.Printf(wxT("%s"), e.what());
			wxMessageBox(msg, _("Get configuration"), wxICON_ERROR);
		}
	}

}

void ZebraCameraDemoFrame::OnButtonRegriveConfigClick(wxCommandEvent& event)
{

	(void)event;

	auto camera = GetCamera();
	if (camera)
	{
		std::string camera_config;

		try
		{
			camera_config = camera_manager_client_->RetrieveConfiguration(camera);
			TextCtrlConfiguration->SetValue(camera_config);
		}
		catch (std::exception& e)
		{
			wxString msg;
			msg.Printf(wxT("%s"), e.what());
			wxMessageBox(msg, _("Retrieve configuration"), wxICON_ERROR);
		}
	}

}

void ZebraCameraDemoFrame::OnButtonLoadConfigClick(wxCommandEvent& event)
{

	(void)event;

	auto camera = GetCamera();
	if (camera)
	{
		std::string camera_configuration = std::string(TextCtrlConfiguration->GetValue());
		if (camera_configuration.compare("") != 0 )
		{
			try
			{
				camera_manager_client_->LoadConfiguration(camera, camera_configuration);

				// Refresh UI controls
				PopulateProcessingUnitInfo(camera);
				PopulateCameraTerminalInfo(camera);
				PopulateExtensionUnit1Info(camera);
			}
			catch (std::exception& e)
			{
				wxString msg;
				msg.Printf(wxT("%s"), e.what());
				wxMessageBox(msg, _("Load configuration into color camera"), wxICON_ERROR);
			}
		}
		else
		{
			wxString msg;
			msg.Printf(wxT("%s"), "load configuration into color camera failed: Empty configuration provided");
			wxMessageBox(msg, _("Load configuration"), wxICON_ERROR);
		}

	}

}

void ZebraCameraDemoFrame::OnButtonClearTextConfigClick(wxCommandEvent& event)
{
	(void)event;

	TextCtrlConfiguration->Clear();
}

