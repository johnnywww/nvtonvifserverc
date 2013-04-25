#include "soapH.h"
#include "soapStub.h"
#include "onvifHandle.h"
#include "appTools.h"
#include "logInfo.h"

#define MAX_PROF_TOKEN 20

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetServiceCapabilities(struct soap* soap,
		struct _trt__GetServiceCapabilities *trt__GetServiceCapabilities,
		struct _trt__GetServiceCapabilitiesResponse *trt__GetServiceCapabilitiesResponse) {
	debugInfo("__trt__GetServiceCapabilities");
	return getOnvifSoapActionNotSupportCode(soap, "GetServiceCapabilities",
			NULL);
}

void getVideoSourcesResponseVideoSource(struct soap* soap,
		struct tt__VideoSource* videoSource,
		OnvifVideoChannelInfo* onvifVideoChannelInfo, int index) {
	videoSource->Framerate = onvifVideoChannelInfo->frame_rate;
	videoSource->Resolution = (struct tt__VideoResolution *) soap_malloc(soap,
			sizeof(struct tt__VideoResolution));
	videoSource->Resolution->Height = onvifVideoChannelInfo->height;
	videoSource->Resolution->Width = onvifVideoChannelInfo->width;
	videoSource->token = (char *) soap_malloc(soap, sizeof(char) * INFO_LENGTH);
	char token[INFO_LENGTH];
	sprintf(token, "%s%d", VIDEO_SOURCE_TOKEN, index);
	strcpy(videoSource->token, token); //注意这里需要和GetProfile中的sourcetoken相同

	videoSource->Imaging = (struct tt__ImagingSettings*) soap_malloc(soap,
			sizeof(struct tt__ImagingSettings));
	videoSource->Imaging->Brightness = (float*) soap_malloc(soap,
			sizeof(float));
	videoSource->Imaging->Brightness[0] = 128;
	videoSource->Imaging->ColorSaturation = (float*) soap_malloc(soap,
			sizeof(float));
	videoSource->Imaging->ColorSaturation[0] = 128;
	videoSource->Imaging->Contrast = (float*) soap_malloc(soap, sizeof(float));
	videoSource->Imaging->Contrast[0] = 128;
	videoSource->Imaging->IrCutFilter =
			(enum tt__IrCutFilterMode *) soap_malloc(soap,
					sizeof(enum tt__IrCutFilterMode));
	*videoSource->Imaging->IrCutFilter = 0;
	videoSource->Imaging->Sharpness = (float*) soap_malloc(soap, sizeof(float));
	videoSource->Imaging->Sharpness[0] = 128;
	videoSource->Imaging->BacklightCompensation =
			(struct tt__BacklightCompensation*) soap_malloc(soap,
					sizeof(struct tt__BacklightCompensation));
	videoSource->Imaging->BacklightCompensation->Mode = 0;
	videoSource->Imaging->BacklightCompensation->Level = 20;
	videoSource->Imaging->Exposure = NULL;
	videoSource->Imaging->Focus = NULL;
	videoSource->Imaging->WideDynamicRange =
			(struct tt__WideDynamicRange*) soap_malloc(soap,
					sizeof(struct tt__WideDynamicRange));
	videoSource->Imaging->WideDynamicRange->Mode = 0;
	videoSource->Imaging->WideDynamicRange->Level = 20;
	videoSource->Imaging->WhiteBalance = (struct tt__WhiteBalance*) soap_malloc(
			soap, sizeof(struct tt__WhiteBalance));
	videoSource->Imaging->WhiteBalance->Mode = 0;
	videoSource->Imaging->WhiteBalance->CrGain = 0;
	videoSource->Imaging->WhiteBalance->CbGain = 0;
	videoSource->Imaging->Extension = NULL;
	videoSource->Extension = NULL;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSources(struct soap* soap,
		struct _trt__GetVideoSources *trt__GetVideoSources,
		struct _trt__GetVideoSourcesResponse *trt__GetVideoSourcesResponse) {
	debugInfo("__trt__GetVideoSources");

	int size1 = 0;
	int ret = getVideoCount(&size1);
	if (!isRetCodeSuccess(ret)) {
		return getOnvifSoapActionFailedCode(soap, "GetVideoSources",
				"getVideCount failed");
	}
	trt__GetVideoSourcesResponse->__sizeVideoSources = size1;
	trt__GetVideoSourcesResponse->VideoSources =
			(struct tt__VideoSource *) soap_malloc(soap,
					sizeof(struct tt__VideoSource) * size1);
	int i = 0;
	for (i = 0; i < size1; i++) {
		OnvifVideoChannelInfo onvifVideoChannelInfo;
		ret = getVideoChannelInfo(&onvifVideoChannelInfo);
		if (!isRetCodeSuccess(ret)) {
			return getOnvifSoapActionFailedCode(soap, "GetVideoSources",
					"getVideoChannelInfo failed");
		}
		getVideoSourcesResponseVideoSource(soap,
				&(trt__GetVideoSourcesResponse->VideoSources[i]),
				&onvifVideoChannelInfo, i);
	}
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSources(struct soap* soap,
		struct _trt__GetAudioSources *trt__GetAudioSources,
		struct _trt__GetAudioSourcesResponse *trt__GetAudioSourcesResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputs(struct soap* soap,
		struct _trt__GetAudioOutputs *trt__GetAudioOutputs,
		struct _trt__GetAudioOutputsResponse *trt__GetAudioOutputsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__CreateProfile(struct soap* soap,
		struct _trt__CreateProfile *trt__CreateProfile,
		struct _trt__CreateProfileResponse *trt__CreateProfileResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetProfile(struct soap* soap,
		struct _trt__GetProfile *trt__GetProfile,
		struct _trt__GetProfileResponse *trt__GetProfileResponse) {
	debugInfo("__trt__GetProfile");
	if (trt__GetProfile) {
		debugInfo("trt__GetProfile=%s", trt__GetProfile->ProfileToken);
	}
	/*这里的ProfileToken是选定的，得到特定的profile描述*/
	//但odm单击一个profile时，需要获取，不然不会出现live video和video streaming
	trt__GetProfileResponse->Profile = (struct tt__Profile *) soap_malloc(soap,
			sizeof(struct tt__Profile));
	trt__GetProfileResponse->Profile->Name = (char *) soap_malloc(soap,
			sizeof(char) * SMALL_INFO_LENGTH);
	trt__GetProfileResponse->Profile->token = (char *) soap_malloc(soap,
			sizeof(char) * SMALL_INFO_LENGTH);
	strcpy(trt__GetProfileResponse->Profile->Name, "my_profile");
	strcpy(trt__GetProfileResponse->Profile->token, "token_profile");
	trt__GetProfileResponse->Profile->fixed = (enum xsd__boolean *) soap_malloc(
			soap, sizeof(enum xsd__boolean));
	*trt__GetProfileResponse->Profile->fixed = xsd__boolean__false_;
	trt__GetProfileResponse->Profile->__anyAttribute = NULL;

	trt__GetProfileResponse->Profile->VideoSourceConfiguration = NULL;
	trt__GetProfileResponse->Profile->AudioSourceConfiguration = NULL;

	/*VideoEncoderConfiguration*/
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration =
			(struct tt__VideoEncoderConfiguration *) soap_malloc(soap,
					sizeof(struct tt__VideoEncoderConfiguration));
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Name =
			(char *) soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->token =
			(char *) soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
	strcpy(trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Name,
			"VE_Name");
	strcpy(trt__GetProfileResponse->Profile->VideoEncoderConfiguration->token,
			"VE_token");
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->UseCount = 1;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Quality = 10;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Encoding = 2; //JPEG = 0, MPEG4 = 1, H264 = 2;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Resolution =
			(struct tt__VideoResolution *) soap_malloc(soap,
					sizeof(struct tt__VideoResolution));
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Resolution->Height =
			720;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Resolution->Width =
			1280;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->RateControl =
			(struct tt__VideoRateControl *) soap_malloc(soap,
					sizeof(struct tt__VideoRateControl));
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->RateControl->FrameRateLimit =
			30;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->RateControl->EncodingInterval =
			1;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->RateControl->BitrateLimit =
			500;

	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->MPEG4 = NULL;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->H264 = NULL;
#if 0
	/*可选，可以不设置*/
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->MPEG4 = (struct tt__Mpeg4Configuration *)soap_malloc(soap, sizeof(struct tt__Mpeg4Configuration));
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->MPEG4->GovLength = 1;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->MPEG4->Mpeg4Profile = 1;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->H264 = (struct tt__H264Configuration *)soap_malloc(soap, sizeof(struct tt__H264Configuration));
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->H264->GovLength = 1;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->H264->H264Profile = 1;
#endif

	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast =
			(struct tt__MulticastConfiguration *) soap_malloc(soap,
					sizeof(struct tt__MulticastConfiguration));
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->Address =
			(struct tt__IPAddress *) soap_malloc(soap,
					sizeof(struct tt__IPAddress));
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->Address->IPv4Address =
			(char **) soap_malloc(soap, sizeof(char *));
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->Address->IPv4Address[0] =
			(char *) soap_malloc(soap, sizeof(char) * INFO_LENGTH);
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->Address->IPv6Address =
			NULL;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->Address->Type =
			0;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->Port =
			554;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->TTL =
			60;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->AutoStart =
			1;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->__size =
			0;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->__any =
			NULL;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->__anyAttribute =
			NULL;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->SessionTimeout =
			720000;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->__size = 0;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->__any = NULL;
	trt__GetProfileResponse->Profile->VideoEncoderConfiguration->__anyAttribute =
			NULL;

	trt__GetProfileResponse->Profile->AudioEncoderConfiguration = NULL;
	trt__GetProfileResponse->Profile->VideoAnalyticsConfiguration = NULL;
	trt__GetProfileResponse->Profile->PTZConfiguration = NULL;
	trt__GetProfileResponse->Profile->MetadataConfiguration = NULL;
	trt__GetProfileResponse->Profile->Extension = NULL;

	return SOAP_OK;
}

void getProfilesResponseProfile(const struct soap* soap,
		const struct tt__Profile* getProfilesResponseProfile,
		const OnvifVideoChannelInfo* onvifVideoChannelInfo, const int index) {
	getProfilesResponseProfile->Name = (char *) soap_malloc(soap,
			sizeof(char) * MAX_PROF_TOKEN);
	strcpy(getProfilesResponseProfile->Name, "my_profile");
	getProfilesResponseProfile->token = (char *) soap_malloc(soap,
			sizeof(char) * MAX_PROF_TOKEN);
	strcpy(getProfilesResponseProfile->token, "token_profile");
	getProfilesResponseProfile->fixed = (enum xsd__boolean *) soap_malloc(soap,
			sizeof(enum xsd__boolean));
	*getProfilesResponseProfile->fixed = xsd__boolean__false_;
	getProfilesResponseProfile->__anyAttribute = NULL;
	getProfilesResponseProfile->VideoAnalyticsConfiguration = NULL;

	/*必须包含VideoEncoderConfiguration的配置
	 不然不会出现live video 和 video streaming*/
	/*VideoEncoderConfiguration*/
	getProfilesResponseProfile->VideoEncoderConfiguration = NULL;
#if 1
	getProfilesResponseProfile->VideoEncoderConfiguration =
			(struct tt__VideoEncoderConfiguration *) soap_malloc(soap,
					sizeof(struct tt__VideoEncoderConfiguration));
	getProfilesResponseProfile->VideoEncoderConfiguration->Name =
			(char *) soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
	getProfilesResponseProfile->VideoEncoderConfiguration->token =
			(char *) soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
	sprintf(getProfilesResponseProfile->VideoEncoderConfiguration->Name,
			"VE_Name%d", index);
	sprintf(getProfilesResponseProfile->VideoEncoderConfiguration->token,
			"VE_token%d", index);
	getProfilesResponseProfile->VideoEncoderConfiguration->UseCount = 1;
	getProfilesResponseProfile->VideoEncoderConfiguration->Quality = 10;
	switch (onvifVideoChannelInfo->enc_type) {
	case 2:
		getProfilesResponseProfile->VideoEncoderConfiguration->Encoding = 0; //JPEG = 0, MPEG4 = 1, H264 = 2;
		break;
	case 1:
		getProfilesResponseProfile->VideoEncoderConfiguration->Encoding = 1; //JPEG = 0, MPEG4 = 1, H264 = 2;
		break;
	default:
		getProfilesResponseProfile->VideoEncoderConfiguration->Encoding = 2; //JPEG = 0, MPEG4 = 1, H264 = 2;
		break;
	}
	getProfilesResponseProfile->VideoEncoderConfiguration->Resolution =
			(struct tt__VideoResolution *) soap_malloc(soap,
					sizeof(struct tt__VideoResolution));
	getProfilesResponseProfile->VideoEncoderConfiguration->Resolution->Height =
			onvifVideoChannelInfo->height;
	getProfilesResponseProfile->VideoEncoderConfiguration->Resolution->Width =
			onvifVideoChannelInfo->width;
	getProfilesResponseProfile->VideoEncoderConfiguration->RateControl =
			(struct tt__VideoRateControl *) soap_malloc(soap,
					sizeof(struct tt__VideoRateControl));
	getProfilesResponseProfile->VideoEncoderConfiguration->RateControl->FrameRateLimit =
			onvifVideoChannelInfo->frame_rate;
	getProfilesResponseProfile->VideoEncoderConfiguration->RateControl->EncodingInterval =
			onvifVideoChannelInfo->encodingInterval;
	getProfilesResponseProfile->VideoEncoderConfiguration->RateControl->BitrateLimit =
			onvifVideoChannelInfo->bit_rate;

	getProfilesResponseProfile->VideoEncoderConfiguration->MPEG4 = NULL;
	getProfilesResponseProfile->VideoEncoderConfiguration->H264 = NULL;
#if 1
	/*可选项，可以不配置*/
	getProfilesResponseProfile->VideoEncoderConfiguration->MPEG4 =
			(struct tt__Mpeg4Configuration *) soap_malloc(soap,
					sizeof(struct tt__Mpeg4Configuration));
	getProfilesResponseProfile->VideoEncoderConfiguration->MPEG4->GovLength =
			30;
	getProfilesResponseProfile->VideoEncoderConfiguration->MPEG4->Mpeg4Profile =
			1;
	getProfilesResponseProfile->VideoEncoderConfiguration->H264 =
			(struct tt__H264Configuration *) soap_malloc(soap,
					sizeof(struct tt__H264Configuration));
	getProfilesResponseProfile->VideoEncoderConfiguration->H264->GovLength = 30;
	getProfilesResponseProfile->VideoEncoderConfiguration->H264->H264Profile =
			1;
#endif
	getProfilesResponseProfile->VideoEncoderConfiguration->Multicast =
			(struct tt__MulticastConfiguration *) soap_malloc(soap,
					sizeof(struct tt__MulticastConfiguration));
	getProfilesResponseProfile->VideoEncoderConfiguration->Multicast->Address =
			(struct tt__IPAddress *) soap_malloc(soap,
					sizeof(struct tt__IPAddress));
	getProfilesResponseProfile->VideoEncoderConfiguration->Multicast->Address->IPv4Address =
			(char **) soap_malloc(soap, sizeof(char *));
	getProfilesResponseProfile->VideoEncoderConfiguration->Multicast->Address->IPv4Address[0] =
			(char *) soap_malloc(soap, sizeof(char) * INFO_LENGTH);
	getProfilesResponseProfile->VideoEncoderConfiguration->Multicast->Address->IPv6Address =
			NULL;
	getProfilesResponseProfile->VideoEncoderConfiguration->Multicast->Address->Type =
			0;
	getProfilesResponseProfile->VideoEncoderConfiguration->Multicast->Port =
			554;
	getProfilesResponseProfile->VideoEncoderConfiguration->Multicast->TTL = 60;
	getProfilesResponseProfile->VideoEncoderConfiguration->Multicast->AutoStart =
			1;
	getProfilesResponseProfile->VideoEncoderConfiguration->Multicast->__size =
			0;
	getProfilesResponseProfile->VideoEncoderConfiguration->Multicast->__any =
			NULL;
	getProfilesResponseProfile->VideoEncoderConfiguration->Multicast->__anyAttribute =
			NULL;
	getProfilesResponseProfile->VideoEncoderConfiguration->SessionTimeout =
			720000;
	getProfilesResponseProfile->VideoEncoderConfiguration->__size = 0;
	getProfilesResponseProfile->VideoEncoderConfiguration->__any = NULL;
	getProfilesResponseProfile->VideoEncoderConfiguration->__anyAttribute = NULL;
#endif

	/* VideoSourceConfiguration */
	//getProfilesResponseProfile->VideoSourceConfiguration = NULL;
	getProfilesResponseProfile->VideoSourceConfiguration =
			(struct tt__VideoSourceConfiguration *) soap_malloc(soap,
					sizeof(struct tt__VideoSourceConfiguration));
	getProfilesResponseProfile->VideoSourceConfiguration->Name =
			(char *) soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
	getProfilesResponseProfile->VideoSourceConfiguration->token =
			(char *) soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
	getProfilesResponseProfile->VideoSourceConfiguration->SourceToken =
			(char *) soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
	getProfilesResponseProfile->VideoSourceConfiguration->Bounds =
			(struct tt__IntRectangle *) soap_malloc(soap,
					sizeof(struct tt__IntRectangle));
	getProfilesResponseProfile->VideoSourceConfiguration->Extension = NULL;
	getProfilesResponseProfile->VideoSourceConfiguration->__any = NULL;
	getProfilesResponseProfile->VideoSourceConfiguration->__anyAttribute = NULL;
	getProfilesResponseProfile->VideoSourceConfiguration->__size = 0;
	/*注意SourceToken*/
	sprintf(getProfilesResponseProfile->VideoSourceConfiguration->Name,
			"VS_Name%d", index);
	sprintf(getProfilesResponseProfile->VideoSourceConfiguration->token,
			"VS_Token%d", index);
	strcpy(getProfilesResponseProfile->VideoSourceConfiguration->SourceToken,
			VIDEO_SOURCE_TOKEN); /*必须与__tmd__GetVideoSources中的token相同*/
	getProfilesResponseProfile->VideoSourceConfiguration->UseCount = 1;
	getProfilesResponseProfile->VideoSourceConfiguration->Bounds->x = 1;
	getProfilesResponseProfile->VideoSourceConfiguration->Bounds->y = 1;
	getProfilesResponseProfile->VideoSourceConfiguration->Bounds->height = 720;
	getProfilesResponseProfile->VideoSourceConfiguration->Bounds->width = 1280;

	getProfilesResponseProfile->AudioEncoderConfiguration = NULL;
	getProfilesResponseProfile->AudioSourceConfiguration = NULL;
	getProfilesResponseProfile->PTZConfiguration = NULL;
	getProfilesResponseProfile->MetadataConfiguration = NULL;
	getProfilesResponseProfile->Extension = NULL;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetProfiles(struct soap* soap,
		struct _trt__GetProfiles *trt__GetProfiles,
		struct _trt__GetProfilesResponse *trt__GetProfilesResponse) {
	debugInfo("__trt__GetProfiles");
	int i;
	int size = 0;
	int ret = getVideoCount(&size);
	if (!isRetCodeSuccess(ret)) {
		return getOnvifSoapActionFailedCode(soap, "GetVideoSources",
				"getVideCount failed");
	}

	trt__GetProfilesResponse->Profiles = (struct tt__Profile *) soap_malloc(
			soap, sizeof(struct tt__Profile) * size);
	trt__GetProfilesResponse->__sizeProfiles = size;

	for (i = 0; i < size; i++) {
		OnvifVideoChannelInfo onvifVideoChannelInfo;
		ret = getVideoChannelInfo(&onvifVideoChannelInfo);
		if (!isRetCodeSuccess(ret)) {
			return getOnvifSoapActionFailedCode(soap, "GetVideoSources",
					"getVideoChannelInfo failed");
		}
		getProfilesResponseProfile(soap,
				&(trt__GetProfilesResponse->Profiles[i]), &onvifVideoChannelInfo, i);
	}
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddVideoEncoderConfiguration(struct soap* soap,
		struct _trt__AddVideoEncoderConfiguration *trt__AddVideoEncoderConfiguration,
		struct _trt__AddVideoEncoderConfigurationResponse *trt__AddVideoEncoderConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddVideoSourceConfiguration(struct soap* soap,
		struct _trt__AddVideoSourceConfiguration *trt__AddVideoSourceConfiguration,
		struct _trt__AddVideoSourceConfigurationResponse *trt__AddVideoSourceConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioEncoderConfiguration(struct soap* soap,
		struct _trt__AddAudioEncoderConfiguration *trt__AddAudioEncoderConfiguration,
		struct _trt__AddAudioEncoderConfigurationResponse *trt__AddAudioEncoderConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioSourceConfiguration(struct soap* soap,
		struct _trt__AddAudioSourceConfiguration *trt__AddAudioSourceConfiguration,
		struct _trt__AddAudioSourceConfigurationResponse *trt__AddAudioSourceConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddPTZConfiguration(struct soap* soap,
		struct _trt__AddPTZConfiguration *trt__AddPTZConfiguration,
		struct _trt__AddPTZConfigurationResponse *trt__AddPTZConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddVideoAnalyticsConfiguration(
		struct soap* soap,
		struct _trt__AddVideoAnalyticsConfiguration *trt__AddVideoAnalyticsConfiguration,
		struct _trt__AddVideoAnalyticsConfigurationResponse *trt__AddVideoAnalyticsConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddMetadataConfiguration(struct soap* soap,
		struct _trt__AddMetadataConfiguration *trt__AddMetadataConfiguration,
		struct _trt__AddMetadataConfigurationResponse *trt__AddMetadataConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioOutputConfiguration(struct soap* soap,
		struct _trt__AddAudioOutputConfiguration *trt__AddAudioOutputConfiguration,
		struct _trt__AddAudioOutputConfigurationResponse *trt__AddAudioOutputConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioDecoderConfiguration(struct soap* soap,
		struct _trt__AddAudioDecoderConfiguration *trt__AddAudioDecoderConfiguration,
		struct _trt__AddAudioDecoderConfigurationResponse *trt__AddAudioDecoderConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveVideoEncoderConfiguration(
		struct soap* soap,
		struct _trt__RemoveVideoEncoderConfiguration *trt__RemoveVideoEncoderConfiguration,
		struct _trt__RemoveVideoEncoderConfigurationResponse *trt__RemoveVideoEncoderConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveVideoSourceConfiguration(
		struct soap* soap,
		struct _trt__RemoveVideoSourceConfiguration *trt__RemoveVideoSourceConfiguration,
		struct _trt__RemoveVideoSourceConfigurationResponse *trt__RemoveVideoSourceConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioEncoderConfiguration(
		struct soap* soap,
		struct _trt__RemoveAudioEncoderConfiguration *trt__RemoveAudioEncoderConfiguration,
		struct _trt__RemoveAudioEncoderConfigurationResponse *trt__RemoveAudioEncoderConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioSourceConfiguration(
		struct soap* soap,
		struct _trt__RemoveAudioSourceConfiguration *trt__RemoveAudioSourceConfiguration,
		struct _trt__RemoveAudioSourceConfigurationResponse *trt__RemoveAudioSourceConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemovePTZConfiguration(struct soap* soap,
		struct _trt__RemovePTZConfiguration *trt__RemovePTZConfiguration,
		struct _trt__RemovePTZConfigurationResponse *trt__RemovePTZConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveVideoAnalyticsConfiguration(
		struct soap* soap,
		struct _trt__RemoveVideoAnalyticsConfiguration *trt__RemoveVideoAnalyticsConfiguration,
		struct _trt__RemoveVideoAnalyticsConfigurationResponse *trt__RemoveVideoAnalyticsConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveMetadataConfiguration(struct soap* soap,
		struct _trt__RemoveMetadataConfiguration *trt__RemoveMetadataConfiguration,
		struct _trt__RemoveMetadataConfigurationResponse *trt__RemoveMetadataConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioOutputConfiguration(
		struct soap* soap,
		struct _trt__RemoveAudioOutputConfiguration *trt__RemoveAudioOutputConfiguration,
		struct _trt__RemoveAudioOutputConfigurationResponse *trt__RemoveAudioOutputConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioDecoderConfiguration(
		struct soap* soap,
		struct _trt__RemoveAudioDecoderConfiguration *trt__RemoveAudioDecoderConfiguration,
		struct _trt__RemoveAudioDecoderConfigurationResponse *trt__RemoveAudioDecoderConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__DeleteProfile(struct soap* soap,
		struct _trt__DeleteProfile *trt__DeleteProfile,
		struct _trt__DeleteProfileResponse *trt__DeleteProfileResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceConfigurations(struct soap* soap,
		struct _trt__GetVideoSourceConfigurations *trt__GetVideoSourceConfigurations,
		struct _trt__GetVideoSourceConfigurationsResponse *trt__GetVideoSourceConfigurationsResponse) {
	debugInfo("__trt__GetVideoSourceConfigurations");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoEncoderConfigurations(
		struct soap* soap,
		struct _trt__GetVideoEncoderConfigurations *trt__GetVideoEncoderConfigurations,
		struct _trt__GetVideoEncoderConfigurationsResponse *trt__GetVideoEncoderConfigurationsResponse) {
	debugInfo("__trt__GetVideoEncoderConfigurations");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSourceConfigurations(struct soap* soap,
		struct _trt__GetAudioSourceConfigurations *trt__GetAudioSourceConfigurations,
		struct _trt__GetAudioSourceConfigurationsResponse *trt__GetAudioSourceConfigurationsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioEncoderConfigurations(
		struct soap* soap,
		struct _trt__GetAudioEncoderConfigurations *trt__GetAudioEncoderConfigurations,
		struct _trt__GetAudioEncoderConfigurationsResponse *trt__GetAudioEncoderConfigurationsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoAnalyticsConfigurations(
		struct soap* soap,
		struct _trt__GetVideoAnalyticsConfigurations *trt__GetVideoAnalyticsConfigurations,
		struct _trt__GetVideoAnalyticsConfigurationsResponse *trt__GetVideoAnalyticsConfigurationsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetMetadataConfigurations(struct soap* soap,
		struct _trt__GetMetadataConfigurations *trt__GetMetadataConfigurations,
		struct _trt__GetMetadataConfigurationsResponse *trt__GetMetadataConfigurationsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputConfigurations(struct soap* soap,
		struct _trt__GetAudioOutputConfigurations *trt__GetAudioOutputConfigurations,
		struct _trt__GetAudioOutputConfigurationsResponse *trt__GetAudioOutputConfigurationsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioDecoderConfigurations(
		struct soap* soap,
		struct _trt__GetAudioDecoderConfigurations *trt__GetAudioDecoderConfigurations,
		struct _trt__GetAudioDecoderConfigurationsResponse *trt__GetAudioDecoderConfigurationsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceConfiguration(struct soap* soap,
		struct _trt__GetVideoSourceConfiguration *trt__GetVideoSourceConfiguration,
		struct _trt__GetVideoSourceConfigurationResponse *trt__GetVideoSourceConfigurationResponse) {
	debugInfo("__tmd__GetVideoSourceConfiguration");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoEncoderConfiguration(struct soap* soap,
		struct _trt__GetVideoEncoderConfiguration *trt__GetVideoEncoderConfiguration,
		struct _trt__GetVideoEncoderConfigurationResponse *trt__GetVideoEncoderConfigurationResponse) {
	debugInfo("__trt__GetVideoEncoderConfiguration");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSourceConfiguration(struct soap* soap,
		struct _trt__GetAudioSourceConfiguration *trt__GetAudioSourceConfiguration,
		struct _trt__GetAudioSourceConfigurationResponse *trt__GetAudioSourceConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioEncoderConfiguration(struct soap* soap,
		struct _trt__GetAudioEncoderConfiguration *trt__GetAudioEncoderConfiguration,
		struct _trt__GetAudioEncoderConfigurationResponse *trt__GetAudioEncoderConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoAnalyticsConfiguration(
		struct soap* soap,
		struct _trt__GetVideoAnalyticsConfiguration *trt__GetVideoAnalyticsConfiguration,
		struct _trt__GetVideoAnalyticsConfigurationResponse *trt__GetVideoAnalyticsConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetMetadataConfiguration(struct soap* soap,
		struct _trt__GetMetadataConfiguration *trt__GetMetadataConfiguration,
		struct _trt__GetMetadataConfigurationResponse *trt__GetMetadataConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputConfiguration(struct soap* soap,
		struct _trt__GetAudioOutputConfiguration *trt__GetAudioOutputConfiguration,
		struct _trt__GetAudioOutputConfigurationResponse *trt__GetAudioOutputConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioDecoderConfiguration(struct soap* soap,
		struct _trt__GetAudioDecoderConfiguration *trt__GetAudioDecoderConfiguration,
		struct _trt__GetAudioDecoderConfigurationResponse *trt__GetAudioDecoderConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleVideoEncoderConfigurations(
		struct soap* soap,
		struct _trt__GetCompatibleVideoEncoderConfigurations *trt__GetCompatibleVideoEncoderConfigurations,
		struct _trt__GetCompatibleVideoEncoderConfigurationsResponse *trt__GetCompatibleVideoEncoderConfigurationsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleVideoSourceConfigurations(
		struct soap* soap,
		struct _trt__GetCompatibleVideoSourceConfigurations *trt__GetCompatibleVideoSourceConfigurations,
		struct _trt__GetCompatibleVideoSourceConfigurationsResponse *trt__GetCompatibleVideoSourceConfigurationsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioEncoderConfigurations(
		struct soap* soap,
		struct _trt__GetCompatibleAudioEncoderConfigurations *trt__GetCompatibleAudioEncoderConfigurations,
		struct _trt__GetCompatibleAudioEncoderConfigurationsResponse *trt__GetCompatibleAudioEncoderConfigurationsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioSourceConfigurations(
		struct soap* soap,
		struct _trt__GetCompatibleAudioSourceConfigurations *trt__GetCompatibleAudioSourceConfigurations,
		struct _trt__GetCompatibleAudioSourceConfigurationsResponse *trt__GetCompatibleAudioSourceConfigurationsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleVideoAnalyticsConfigurations(
		struct soap* soap,
		struct _trt__GetCompatibleVideoAnalyticsConfigurations *trt__GetCompatibleVideoAnalyticsConfigurations,
		struct _trt__GetCompatibleVideoAnalyticsConfigurationsResponse *trt__GetCompatibleVideoAnalyticsConfigurationsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleMetadataConfigurations(
		struct soap* soap,
		struct _trt__GetCompatibleMetadataConfigurations *trt__GetCompatibleMetadataConfigurations,
		struct _trt__GetCompatibleMetadataConfigurationsResponse *trt__GetCompatibleMetadataConfigurationsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioOutputConfigurations(
		struct soap* soap,
		struct _trt__GetCompatibleAudioOutputConfigurations *trt__GetCompatibleAudioOutputConfigurations,
		struct _trt__GetCompatibleAudioOutputConfigurationsResponse *trt__GetCompatibleAudioOutputConfigurationsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioDecoderConfigurations(
		struct soap* soap,
		struct _trt__GetCompatibleAudioDecoderConfigurations *trt__GetCompatibleAudioDecoderConfigurations,
		struct _trt__GetCompatibleAudioDecoderConfigurationsResponse *trt__GetCompatibleAudioDecoderConfigurationsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoSourceConfiguration(struct soap* soap,
		struct _trt__SetVideoSourceConfiguration *trt__SetVideoSourceConfiguration,
		struct _trt__SetVideoSourceConfigurationResponse *trt__SetVideoSourceConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoEncoderConfiguration(struct soap* soap,
		struct _trt__SetVideoEncoderConfiguration *trt__SetVideoEncoderConfiguration,
		struct _trt__SetVideoEncoderConfigurationResponse *trt__SetVideoEncoderConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioSourceConfiguration(struct soap* soap,
		struct _trt__SetAudioSourceConfiguration *trt__SetAudioSourceConfiguration,
		struct _trt__SetAudioSourceConfigurationResponse *trt__SetAudioSourceConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioEncoderConfiguration(struct soap* soap,
		struct _trt__SetAudioEncoderConfiguration *trt__SetAudioEncoderConfiguration,
		struct _trt__SetAudioEncoderConfigurationResponse *trt__SetAudioEncoderConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoAnalyticsConfiguration(
		struct soap* soap,
		struct _trt__SetVideoAnalyticsConfiguration *trt__SetVideoAnalyticsConfiguration,
		struct _trt__SetVideoAnalyticsConfigurationResponse *trt__SetVideoAnalyticsConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetMetadataConfiguration(struct soap* soap,
		struct _trt__SetMetadataConfiguration *trt__SetMetadataConfiguration,
		struct _trt__SetMetadataConfigurationResponse *trt__SetMetadataConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioOutputConfiguration(struct soap* soap,
		struct _trt__SetAudioOutputConfiguration *trt__SetAudioOutputConfiguration,
		struct _trt__SetAudioOutputConfigurationResponse *trt__SetAudioOutputConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioDecoderConfiguration(struct soap* soap,
		struct _trt__SetAudioDecoderConfiguration *trt__SetAudioDecoderConfiguration,
		struct _trt__SetAudioDecoderConfigurationResponse *trt__SetAudioDecoderConfigurationResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceConfigurationOptions(
		struct soap* soap,
		struct _trt__GetVideoSourceConfigurationOptions *trt__GetVideoSourceConfigurationOptions,
		struct _trt__GetVideoSourceConfigurationOptionsResponse *trt__GetVideoSourceConfigurationOptionsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoEncoderConfigurationOptions(
		struct soap* soap,
		struct _trt__GetVideoEncoderConfigurationOptions *trt__GetVideoEncoderConfigurationOptions,
		struct _trt__GetVideoEncoderConfigurationOptionsResponse *trt__GetVideoEncoderConfigurationOptionsResponse) {
	debugInfo("__trt__GetVideoEncoderConfigurationOptions");
	//该函数必要，video streaming需要
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSourceConfigurationOptions(
		struct soap* soap,
		struct _trt__GetAudioSourceConfigurationOptions *trt__GetAudioSourceConfigurationOptions,
		struct _trt__GetAudioSourceConfigurationOptionsResponse *trt__GetAudioSourceConfigurationOptionsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioEncoderConfigurationOptions(
		struct soap* soap,
		struct _trt__GetAudioEncoderConfigurationOptions *trt__GetAudioEncoderConfigurationOptions,
		struct _trt__GetAudioEncoderConfigurationOptionsResponse *trt__GetAudioEncoderConfigurationOptionsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetMetadataConfigurationOptions(
		struct soap* soap,
		struct _trt__GetMetadataConfigurationOptions *trt__GetMetadataConfigurationOptions,
		struct _trt__GetMetadataConfigurationOptionsResponse *trt__GetMetadataConfigurationOptionsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputConfigurationOptions(
		struct soap* soap,
		struct _trt__GetAudioOutputConfigurationOptions *trt__GetAudioOutputConfigurationOptions,
		struct _trt__GetAudioOutputConfigurationOptionsResponse *trt__GetAudioOutputConfigurationOptionsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioDecoderConfigurationOptions(
		struct soap* soap,
		struct _trt__GetAudioDecoderConfigurationOptions *trt__GetAudioDecoderConfigurationOptions,
		struct _trt__GetAudioDecoderConfigurationOptionsResponse *trt__GetAudioDecoderConfigurationOptionsResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetGuaranteedNumberOfVideoEncoderInstances(
		struct soap* soap,
		struct _trt__GetGuaranteedNumberOfVideoEncoderInstances *trt__GetGuaranteedNumberOfVideoEncoderInstances,
		struct _trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse *trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse) {
	debugInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetStreamUri(struct soap* soap,
		struct _trt__GetStreamUri *trt__GetStreamUri,
		struct _trt__GetStreamUriResponse *trt__GetStreamUriResponse) {
	debugInfo("__trt__GetStreamUri");
	char _IPAddr[INFO_LENGTH];
	strcpy(_IPAddr, onvifRunParam.ip);
	char _IPAddr1[INFO_LENGTH] = { 0 };
	sprintf(_IPAddr, "rtsp://%s:8554/day.264", _IPAddr1);
	/* Response */
	trt__GetStreamUriResponse->MediaUri = (struct tt__MediaUri *) soap_malloc(
			soap, sizeof(struct tt__MediaUri));
	trt__GetStreamUriResponse->MediaUri->Uri = (char *) soap_malloc(soap,
			sizeof(char) * LARGE_INFO_LENGTH);
	strcpy(trt__GetStreamUriResponse->MediaUri->Uri, _IPAddr);
	trt__GetStreamUriResponse->MediaUri->InvalidAfterConnect = 0;
	trt__GetStreamUriResponse->MediaUri->InvalidAfterReboot = 0;
	trt__GetStreamUriResponse->MediaUri->Timeout = 200;
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__StartMulticastStreaming(struct soap* soap,
		struct _trt__StartMulticastStreaming *trt__StartMulticastStreaming,
		struct _trt__StartMulticastStreamingResponse *trt__StartMulticastStreamingResponse) {
	debugInfo("__trt__StartMulticastStreaming");
	return getOnvifSoapActionNotSupportCode(soap, "StartMulticastStreaming",
			NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__StopMulticastStreaming(struct soap* soap,
		struct _trt__StopMulticastStreaming *trt__StopMulticastStreaming,
		struct _trt__StopMulticastStreamingResponse *trt__StopMulticastStreamingResponse) {
	debugInfo("__trt__StopMulticastStreaming");
	return getOnvifSoapActionNotSupportCode(soap, "StopMulticastStreaming",
			NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetSynchronizationPoint(struct soap* soap,
		struct _trt__SetSynchronizationPoint *trt__SetSynchronizationPoint,
		struct _trt__SetSynchronizationPointResponse *trt__SetSynchronizationPointResponse) {
	debugInfo("__trt__SetSynchronizationPoint");
	return getOnvifSoapActionNotSupportCode(soap, "SetSynchronizationPoint",
			NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetSnapshotUri(struct soap* soap,
		struct _trt__GetSnapshotUri *trt__GetSnapshotUri,
		struct _trt__GetSnapshotUriResponse *trt__GetSnapshotUriResponse) {
	debugInfo("__trt__GetSnapshotUri");
	trt__GetSnapshotUriResponse->MediaUri = (struct tt__MediaUri *) soap_malloc(
			soap, sizeof(struct tt__MediaUri));
	trt__GetSnapshotUriResponse->MediaUri->Uri = (char *) soap_malloc(soap,
			sizeof(char) * 200);
	strcpy(trt__GetSnapshotUriResponse->MediaUri->Uri,
			"http://avatar.csdn.net/7/E/1/1_ghostyu.jpg");
	trt__GetSnapshotUriResponse->MediaUri->InvalidAfterConnect = 0;
	trt__GetSnapshotUriResponse->MediaUri->InvalidAfterReboot = 0;
	trt__GetSnapshotUriResponse->MediaUri->Timeout = 2; //seconds
	trt__GetSnapshotUriResponse->MediaUri->__size = 0;
	trt__GetSnapshotUriResponse->MediaUri->__any = NULL;
	trt__GetSnapshotUriResponse->MediaUri->__anyAttribute = NULL;
	return SOAP_OK;
}

