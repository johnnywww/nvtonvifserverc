#include <misc.h>
#include "soapH.h"
#include "soapStub.h"
#include "onvifHandle.h"
#include "appCommon.h"
#include "appTools.h"
#include "logInfo.h"

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetServices(struct soap* soap,
		struct _tds__GetServices *tds__GetServices,
		struct _tds__GetServicesResponse *tds__GetServicesResponse) {
	logInfo("__tds__GetServices");
	char _xmAddr[INFO_LENGTH] = { 0 };
	if (RET_CODE_SUCCESS != getServiceURL(_xmAddr, onvifRunParam.ip, onvifRunParam.servicePort)) {
		return getOnvifSoapActionFailedCode(soap, "GetServices",
				"not get service url");
	}
	tds__GetServicesResponse->__sizeService = 1;
	if (!tds__GetServices->IncludeCapability) {
		tds__GetServicesResponse->Service = (struct tds__Service *) soap_malloc(
				soap, sizeof(struct tds__Service));
		tds__GetServicesResponse->Service[0].XAddr = (char *) soap_malloc(soap,
				sizeof(char) * INFO_LENGTH);
		tds__GetServicesResponse->Service[0].Namespace = (char *) soap_malloc(
				soap, sizeof(char) * INFO_LENGTH);
		strcpy(tds__GetServicesResponse->Service[0].Namespace,
				"http://www.onvif.org/ver10/events/wsdl");
		strcpy(tds__GetServicesResponse->Service[0].XAddr, _xmAddr);
		tds__GetServicesResponse->Service[0].Capabilities = NULL;
		tds__GetServicesResponse->Service[0].Version =
				(struct tt__OnvifVersion *) soap_malloc(soap,
						sizeof(struct tt__OnvifVersion));
		tds__GetServicesResponse->Service[0].Version->Major = 0;
		tds__GetServicesResponse->Service[0].Version->Minor = 3;
//		tds__GetServicesResponse->Service[0].__any = (char **)soap_malloc(soap, sizeof(char *));
//		tds__GetServicesResponse->Service[0].__any[0] = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
//		strcpy(tds__GetServicesResponse->Service[0].__any[0],"Any1");
//		tds__GetServicesResponse->Service[0].__any[1] = (char *)soap_malloc(soap,sizeof(char) * INFO_LENGTH);
//		strcpy(tds__GetServicesResponse->Service[0].__any[1],"Any2");
		tds__GetServicesResponse->Service[0].__size = 0;
		tds__GetServicesResponse->Service[0].__anyAttribute = NULL;
		tds__GetServicesResponse->Service[0].__any = NULL;
		return SOAP_OK;
	} else {
		tds__GetServicesResponse->Service = (struct tds__Service *) soap_malloc(
				soap, sizeof(struct tds__Service));
		tds__GetServicesResponse->Service->XAddr = (char *) soap_malloc(soap,
				sizeof(char) * INFO_LENGTH);
		tds__GetServicesResponse->__sizeService = 1;
		tds__GetServicesResponse->Service->Namespace = NULL;
		strcpy(tds__GetServicesResponse->Service->XAddr, _xmAddr);
		tds__GetServicesResponse->Service->Capabilities = NULL;
		tds__GetServicesResponse->Service->Version =
				(struct tt__OnvifVersion *) soap_malloc(soap,
						sizeof(struct tt__OnvifVersion));
		tds__GetServicesResponse->Service->Version->Major = 0;
		tds__GetServicesResponse->Service->Version->Minor = 3;
		tds__GetServicesResponse->Service->__size = 2;
		char** pot = (char **) soap_malloc(soap,
				sizeof(char *) * tds__GetServicesResponse->Service->__size);

		pot[0] = (char *) soap_malloc(soap, sizeof(char) * INFO_LENGTH);
		strcpy(pot[0], "Any1");
		pot[1] = (char *) soap_malloc(soap, sizeof(char) * INFO_LENGTH);
		strcpy(pot[1], "Any2");
		tds__GetServicesResponse->Service->__any = pot;
		tds__GetServicesResponse->Service->__anyAttribute = NULL;
	}
	return SOAP_OK;
}

void getServiceCapabilitiesNetworkSettings(struct soap* soap, struct _tds__GetServiceCapabilitiesResponse *tds__GetServiceCapabilitiesResponse) {
	/* NETWORK */
	tds__GetServiceCapabilitiesResponse->Capabilities->Network =
			(struct tds__NetworkCapabilities *) soap_malloc(soap,
					sizeof(struct tds__NetworkCapabilities));
	tds__GetServiceCapabilitiesResponse->Capabilities->Network->IPFilter =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	tds__GetServiceCapabilitiesResponse->Capabilities->Network->ZeroConfiguration =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	tds__GetServiceCapabilitiesResponse->Capabilities->Network->IPVersion6 =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	tds__GetServiceCapabilitiesResponse->Capabilities->Network->DynDNS =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	tds__GetServiceCapabilitiesResponse->Capabilities->Network->Dot11Configuration =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	tds__GetServiceCapabilitiesResponse->Capabilities->Network->HostnameFromDHCP =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->Network->IPFilter = xsd__boolean__false_;

	*tds__GetServiceCapabilitiesResponse->Capabilities->Network->ZeroConfiguration =
			xsd__boolean__false_;
	*tds__GetServiceCapabilitiesResponse->Capabilities->Network->IPVersion6 =
			xsd__boolean__false_;
	*tds__GetServiceCapabilitiesResponse->Capabilities->Network->DynDNS =
			xsd__boolean__false_;
	*tds__GetServiceCapabilitiesResponse->Capabilities->Network->Dot11Configuration =
			xsd__boolean__false_;
	*tds__GetServiceCapabilitiesResponse->Capabilities->Network->HostnameFromDHCP =
			xsd__boolean__false_;
	*tds__GetServiceCapabilitiesResponse->Capabilities->Network->NTP = 1;
}

void getServiceCapabilitiesSystemSettings(struct soap* soap, struct _tds__GetServiceCapabilitiesResponse *tds__GetServiceCapabilitiesResponse) {
	/* SYSTEM */
	tds__GetServiceCapabilitiesResponse->Capabilities->System =
			(struct tds__SystemCapabilities *) soap_malloc(soap,
					sizeof(struct tds__SystemCapabilities));
	tds__GetServiceCapabilitiesResponse->Capabilities->System->DiscoveryResolve =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->System->DiscoveryResolve =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->System->DiscoveryBye =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->System->DiscoveryBye =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->System->RemoteDiscovery =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->System->RemoteDiscovery =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->System->SystemBackup =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->System->SystemBackup =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->System->FirmwareUpgrade =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->System->FirmwareUpgrade =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->System->SystemLogging =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->System->SystemLogging =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->System->HttpSystemBackup =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->System->HttpSystemBackup =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->System->HttpFirmwareUpgrade =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->System->HttpFirmwareUpgrade =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->System->HttpSystemLogging =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->System->HttpSystemLogging =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->System->HttpSupportInformation =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->System->HttpSupportInformation =
			xsd__boolean__false_;
}

void getServiceCapabilitiesSecuritySettings(struct soap* soap, struct _tds__GetServiceCapabilitiesResponse *tds__GetServiceCapabilitiesResponse) {
	/* SECURITY */
	tds__GetServiceCapabilitiesResponse->Capabilities->Security =
			(struct tds__SecurityCapabilities *) soap_malloc(soap,
					sizeof(struct tds__SecurityCapabilities));
	tds__GetServiceCapabilitiesResponse->Capabilities->Security->TLS1_x002e0 =
				(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->Security->TLS1_x002e0 =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->Security->TLS1_x002e1 =
				(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->Security->TLS1_x002e1 =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->Security->TLS1_x002e2 =
				(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->Security->TLS1_x002e2 =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->Security->OnboardKeyGeneration =
				(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->Security->OnboardKeyGeneration =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->Security->AccessPolicyConfig =
				(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->Security->AccessPolicyConfig =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->Security->Dot1X =
				(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->Security->Dot1X = xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->Security->RemoteUserHandling =
				(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->Security->RemoteUserHandling =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->Security->X_x002e509Token =
				(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->Security->X_x002e509Token =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->Security->SAMLToken =
				(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->Security->SAMLToken =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->Security->KerberosToken =
				(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->Security->KerberosToken =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->Security->UsernameToken =
				(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->Security->UsernameToken =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->Security->HttpDigest =
				(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->Security->HttpDigest =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->Security->RELToken =
				(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetServiceCapabilitiesResponse->Capabilities->Security->RELToken =
			xsd__boolean__false_;
	tds__GetServiceCapabilitiesResponse->Capabilities->Security->SupportedEAPMethods =
			NULL;
	tds__GetServiceCapabilitiesResponse->Capabilities->Security->__anyAttribute =
			NULL;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetServiceCapabilities(
		struct soap* soap,
		struct _tds__GetServiceCapabilities *tds__GetServiceCapabilities,
		struct _tds__GetServiceCapabilitiesResponse *tds__GetServiceCapabilitiesResponse) {
	logInfo("__tds__GetServiceCapabilities");
	tds__GetServiceCapabilitiesResponse->Capabilities =
			(struct tds__DeviceServiceCapabilities *) soap_malloc(soap,
					sizeof(struct tds__DeviceServiceCapabilities));

	getServiceCapabilitiesNetworkSettings(soap, tds__GetServiceCapabilitiesResponse);
	getServiceCapabilitiesSystemSettings(soap, tds__GetServiceCapabilitiesResponse);
	getServiceCapabilitiesSecuritySettings(soap, tds__GetServiceCapabilitiesResponse);

	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDeviceInformation(
		struct soap* soap,
		struct _tds__GetDeviceInformation *tds__GetDeviceInformation,
		struct _tds__GetDeviceInformationResponse *tds__GetDeviceInformationResponse) {
	OnvifDeviceInfo info;
	if (!isRetCodeSuccess(getDeviceInfo(&info))) {
		return getOnvifSoapActionFailedCode(soap, "GetDeviceInformation",
						"not get deviceinfo");
	}
	tds__GetDeviceInformationResponse->HardwareId = (char *) soap_malloc(soap,
			INFO_LENGTH);
	strcpy(tds__GetDeviceInformationResponse->HardwareId, info.hardwareId);
	tds__GetDeviceInformationResponse->FirmwareVersion = (char *) soap_malloc(
			soap, INFO_LENGTH);
	strcpy(tds__GetDeviceInformationResponse->FirmwareVersion, info.firmwareVersion);
	tds__GetDeviceInformationResponse->Manufacturer = (char *) soap_malloc(soap,
			INFO_LENGTH);
	strcpy(tds__GetDeviceInformationResponse->Manufacturer, info.manufacturer);
	tds__GetDeviceInformationResponse->Model = (char *) soap_malloc(soap, INFO_LENGTH);
	strcpy(tds__GetDeviceInformationResponse->Model, info.model);
	tds__GetDeviceInformationResponse->SerialNumber = (char *) soap_malloc(soap,
			INFO_LENGTH);
	strcpy(tds__GetDeviceInformationResponse->SerialNumber, info.serialNumber);
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetSystemDateAndTime(
		struct soap* soap,
		struct _tds__SetSystemDateAndTime *tds__SetSystemDateAndTime,
		struct _tds__SetSystemDateAndTimeResponse *tds__SetSystemDateAndTimeResponse) {
	logInfo("__tds__SetSystemDateAndTime");
	return getOnvifSoapActionNotSupportCode(soap, "SetSystemDateAndTime", NULL);

}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemDateAndTime(
		struct soap* soap,
		struct _tds__GetSystemDateAndTime *tds__GetSystemDateAndTime,
		struct _tds__GetSystemDateAndTimeResponse *tds__GetSystemDateAndTimeResponse) {
	logInfo("__tds__GetSystemDateAndTime");
	return getOnvifSoapActionNotSupportCode(soap, "GetSystemDateAndTime", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetSystemFactoryDefault(
		struct soap* soap,
		struct _tds__SetSystemFactoryDefault *tds__SetSystemFactoryDefault,
		struct _tds__SetSystemFactoryDefaultResponse *tds__SetSystemFactoryDefaultResponse) {
	logInfo("__tds__SetSystemFactoryDefault");
	if (!isRetCodeSuccess(setSystemFactoryDefault())) {
		return getOnvifSoapActionFailedCode(soap, "RestoreSystem",
						"restore failed");
	}
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__UpgradeSystemFirmware(
		struct soap* soap,
		struct _tds__UpgradeSystemFirmware *tds__UpgradeSystemFirmware,
		struct _tds__UpgradeSystemFirmwareResponse *tds__UpgradeSystemFirmwareResponse) {
	logInfo("__tds__UpgradeSystemFirmware");
	return getOnvifSoapActionNotSupportCode(soap, "UpgradeSystemFirmware", NULL);

}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SystemReboot(struct soap* soap,
		struct _tds__SystemReboot *tds__SystemReboot,
		struct _tds__SystemRebootResponse *tds__SystemRebootResponse) {
	logInfo("__tds__SystemReboot");
	if (!isRetCodeSuccess(deviceReboot())) {
		return getOnvifSoapActionFailedCode(soap, "SystemReboot",
						"reboot failed");
	}
	tds__SystemRebootResponse->Message = (char*) soap_malloc(soap, INFO_LENGTH);
	strcpy(tds__SystemRebootResponse->Message, "Rebooting in 5 seconds.");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__RestoreSystem(struct soap* soap,
		struct _tds__RestoreSystem *tds__RestoreSystem,
		struct _tds__RestoreSystemResponse *tds__RestoreSystemResponse) {
	logInfo("__tds__RestoreSystem");
	return getOnvifSoapActionNotSupportCode(soap, "RestoreSystem", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemBackup(struct soap* soap,
		struct _tds__GetSystemBackup *tds__GetSystemBackup,
		struct _tds__GetSystemBackupResponse *tds__GetSystemBackupResponse) {
	logInfo("__tds__GetSystemBackup");
	return getOnvifSoapActionNotSupportCode(soap, "RestoreSystem", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemLog(struct soap* soap,
		struct _tds__GetSystemLog *tds__GetSystemLog,
		struct _tds__GetSystemLogResponse *tds__GetSystemLogResponse) {
	logInfo("__tds__GetSystemLog");
	return getOnvifSoapActionNotSupportCode(soap, "GetSystemLog", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemSupportInformation(
		struct soap* soap,
		struct _tds__GetSystemSupportInformation *tds__GetSystemSupportInformation,
		struct _tds__GetSystemSupportInformationResponse *tds__GetSystemSupportInformationResponse) {
	logInfo("__tds__GetSystemSupportInformation");
	return getOnvifSoapActionNotSupportCode(soap, "GetSystemSupportInformation", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetScopes(struct soap* soap,
		struct _tds__GetScopes *tds__GetScopes,
		struct _tds__GetScopesResponse *tds__GetScopesResponse) {
	logInfo("__tds__GetScopes");
	int size = 1;
	tds__GetScopesResponse->__sizeScopes = size;
	tds__GetScopesResponse->Scopes = (struct tt__Scope*) soap_malloc(soap,
			size * sizeof(struct tt__Scope));
	tds__GetScopesResponse->Scopes->ScopeItem = (char*) soap_malloc(soap, INFO_LENGTH);
	tds__GetScopesResponse->Scopes->ScopeDef = 0;
	strcpy(tds__GetScopesResponse->Scopes->ScopeItem, ONVIF_SCOPE_NAME);
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetScopes(struct soap* soap,
		struct _tds__SetScopes *tds__SetScopes,
		struct _tds__SetScopesResponse *tds__SetScopesResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetScopes", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__AddScopes(struct soap* soap,
		struct _tds__AddScopes *tds__AddScopes,
		struct _tds__AddScopesResponse *tds__AddScopesResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "AddScopes", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__RemoveScopes(struct soap* soap,
		struct _tds__RemoveScopes *tds__RemoveScopes,
		struct _tds__RemoveScopesResponse *tds__RemoveScopesResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "RemoveScopes", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDiscoveryMode(struct soap* soap,
		struct _tds__GetDiscoveryMode *tds__GetDiscoveryMode,
		struct _tds__GetDiscoveryModeResponse *tds__GetDiscoveryModeResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetDiscoveryMode", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDiscoveryMode(struct soap* soap,
		struct _tds__SetDiscoveryMode *tds__SetDiscoveryMode,
		struct _tds__SetDiscoveryModeResponse *tds__SetDiscoveryModeResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetDiscoveryMode", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetRemoteDiscoveryMode(
		struct soap* soap,
		struct _tds__GetRemoteDiscoveryMode *tds__GetRemoteDiscoveryMode,
		struct _tds__GetRemoteDiscoveryModeResponse *tds__GetRemoteDiscoveryModeResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetRemoteDiscoveryMode", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRemoteDiscoveryMode(
		struct soap* soap,
		struct _tds__SetRemoteDiscoveryMode *tds__SetRemoteDiscoveryMode,
		struct _tds__SetRemoteDiscoveryModeResponse *tds__SetRemoteDiscoveryModeResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetRemoteDiscoveryMode", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDPAddresses(struct soap* soap,
		struct _tds__GetDPAddresses *tds__GetDPAddresses,
		struct _tds__GetDPAddressesResponse *tds__GetDPAddressesResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetDPAddresses", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetEndpointReference(
		struct soap* soap,
		struct _tds__GetEndpointReference *tds__GetEndpointReference,
		struct _tds__GetEndpointReferenceResponse *tds__GetEndpointReferenceResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetEndpointReference", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetRemoteUser(struct soap* soap,
		struct _tds__GetRemoteUser *tds__GetRemoteUser,
		struct _tds__GetRemoteUserResponse *tds__GetRemoteUserResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetRemoteUser", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRemoteUser(struct soap* soap,
		struct _tds__SetRemoteUser *tds__SetRemoteUser,
		struct _tds__SetRemoteUserResponse *tds__SetRemoteUserResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetRemoteUser", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetUsers(struct soap* soap,
		struct _tds__GetUsers *tds__GetUsers,
		struct _tds__GetUsersResponse *tds__GetUsersResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetUsers", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__CreateUsers(struct soap* soap,
		struct _tds__CreateUsers *tds__CreateUsers,
		struct _tds__CreateUsersResponse *tds__CreateUsersResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "CreateUsers", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__DeleteUsers(struct soap* soap,
		struct _tds__DeleteUsers *tds__DeleteUsers,
		struct _tds__DeleteUsersResponse *tds__DeleteUsersResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "DeleteUsers", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetUser(struct soap* soap,
		struct _tds__SetUser *tds__SetUser,
		struct _tds__SetUserResponse *tds__SetUserResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetUser", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetWsdlUrl(struct soap* soap,
		struct _tds__GetWsdlUrl *tds__GetWsdlUrl,
		struct _tds__GetWsdlUrlResponse *tds__GetWsdlUrlResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetWsdlUrl", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCapabilities(struct soap* soap,
		struct _tds__GetCapabilities *tds__GetCapabilities,
		struct _tds__GetCapabilitiesResponse *tds__GetCapabilitiesResponse) {
	logInfo("__tds__GetCapabilities");
	char _IPv4Address[LARGE_INFO_LENGTH];
	if (RET_CODE_SUCCESS
			!= getServiceURL(_IPv4Address, onvifRunParam.ip, onvifRunParam.servicePort))
		return getOnvifSoapActionFailedCode(soap, "GetCapabilities",
				"not get service url");;
	if (tds__GetCapabilities->Category == NULL)
	{
		tds__GetCapabilities->Category = (enum tt__CapabilityCategory *) soap_malloc(soap, sizeof(enum tt__CapabilityCategory));
		*tds__GetCapabilities->Category = ALL;
	}

	tds__GetCapabilitiesResponse->Capabilities =
			(struct tt__Capabilities*) soap_malloc(soap,
					sizeof(struct tt__Capabilities));
	tds__GetCapabilitiesResponse->Capabilities->Analytics = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Device = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Events = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Imaging = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Media = NULL;
	tds__GetCapabilitiesResponse->Capabilities->PTZ = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Extension =
			(struct tt__CapabilitiesExtension*) soap_malloc(soap,
					sizeof(struct tt__CapabilitiesExtension));
	tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO =
			(struct tt__DeviceIOCapabilities*) soap_malloc(soap,
					sizeof(struct tt__DeviceIOCapabilities));
	tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->XAddr =
			(char *) soap_malloc(soap, sizeof(char) * INFO_LENGTH);
	strcpy(
			tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->XAddr,
			_IPv4Address);
	int vSource = 0;
	int ret = getVideoCount(&vSource);
	if (!isRetCodeSuccess(ret)) {
		return getOnvifSoapActionFailedCode(soap, "GetCapabilities",
				"getVideCount failed");
	}
	//下面的重要，这里只实现视频流，需要设置VideoSources
	tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->VideoSources =
			vSource;
	tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->VideoOutputs =
			0;
	tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->AudioSources =
			0;
	tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->AudioOutputs =
			0;
	tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->RelayOutputs =
			0;
	tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->__size = 0;
	tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->__any =
			NULL;

	tds__GetCapabilitiesResponse->Capabilities->Extension->Display = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Extension->Recording = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Extension->Search = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Extension->Replay = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Extension->Receiver = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Extension->AnalyticsDevice =
			NULL;
	tds__GetCapabilitiesResponse->Capabilities->Extension->Extensions = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Extension->__size = 0;
	tds__GetCapabilitiesResponse->Capabilities->Extension->__any = NULL;

	/*基础设置，很必须*/
	tds__GetCapabilitiesResponse->Capabilities->Device =
			(struct tt__DeviceCapabilities*) soap_malloc(soap,
					sizeof(struct tt__DeviceCapabilities));
	tds__GetCapabilitiesResponse->Capabilities->Device->XAddr =
			(char *) soap_malloc(soap, sizeof(char) * LARGE_INFO_LENGTH);
	strcpy(tds__GetCapabilitiesResponse->Capabilities->Device->XAddr,
			_IPv4Address);
	tds__GetCapabilitiesResponse->Capabilities->Device->Extension = NULL;

	/*必要部分*/
	tds__GetCapabilitiesResponse->Capabilities->Device->Network =
			(struct tt__NetworkCapabilities*) soap_malloc(soap,
					sizeof(struct tt__NetworkCapabilities));
	tds__GetCapabilitiesResponse->Capabilities->Device->Network->IPFilter =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	tds__GetCapabilitiesResponse->Capabilities->Device->Network->ZeroConfiguration =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	tds__GetCapabilitiesResponse->Capabilities->Device->Network->IPVersion6 =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	tds__GetCapabilitiesResponse->Capabilities->Device->Network->DynDNS =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));

	*tds__GetCapabilitiesResponse->Capabilities->Device->Network->IPFilter =
			xsd__boolean__false_;
	*tds__GetCapabilitiesResponse->Capabilities->Device->Network->ZeroConfiguration =
			xsd__boolean__false_;
	*tds__GetCapabilitiesResponse->Capabilities->Device->Network->IPVersion6 =
			xsd__boolean__false_;
	*tds__GetCapabilitiesResponse->Capabilities->Device->Network->DynDNS =
			xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->Network->Extension =
			(struct tt__NetworkCapabilitiesExtension*) soap_malloc(soap,
					sizeof(struct tt__NetworkCapabilitiesExtension));
	tds__GetCapabilitiesResponse->Capabilities->Device->Network->Extension->Dot11Configuration =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->Network->Extension->Dot11Configuration =
			xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->Network->Extension->Extension =
			NULL;
	/*ghostyu  MUST BE*/
	tds__GetCapabilitiesResponse->Capabilities->Device->Network->Extension->__size =
			0;
	tds__GetCapabilitiesResponse->Capabilities->Device->Network->Extension->__any =
			NULL;

	tds__GetCapabilitiesResponse->Capabilities->Device->System = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Device->IO = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Device->Security = NULL;
#if 0
	tds__GetCapabilitiesResponse->Capabilities->Device->System = (struct tt__SystemCapabilities*)soap_malloc(soap, sizeof(struct tt__SystemCapabilities));
	tds__GetCapabilitiesResponse->Capabilities->Device->System->DiscoveryResolve =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->System->DiscoveryResolve = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->DiscoveryBye =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->System->DiscoveryBye = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->RemoteDiscovery =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->System->RemoteDiscovery = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->SystemBackup =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->System->SystemBackup = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->SystemLogging =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->System->SystemLogging = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->FirmwareUpgrade =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->System->FirmwareUpgrade = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->__sizeSupportedVersions =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->System->__sizeSupportedVersions = xsd__boolean__true_;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->SupportedVersions = (struct tt__OnvifVersion*)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
	tds__GetCapabilitiesResponse->Capabilities->Device->System->SupportedVersions->Major = MAJOR;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->SupportedVersions->Minor = MINOR;

	tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension = (struct tt__SystemCapabilitiesExtension*)soap_malloc(soap, sizeof(struct tt__SystemCapabilitiesExtension));
	tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpSystemBackup = (enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpSystemBackup = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpFirmwareUpgrade = (enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpFirmwareUpgrade = xsd__boolean__true_;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpSystemLogging = (enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpSystemLogging = xsd__boolean__true_;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpSupportInformation = (enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpSupportInformation = xsd__boolean__true_;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->Extension = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->__size = 0;
	tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->__any = NULL;

	tds__GetCapabilitiesResponse->Capabilities->Device->IO = (struct tt__IOCapabilities*)soap_malloc(soap, sizeof(struct tt__IOCapabilities));
	tds__GetCapabilitiesResponse->Capabilities->Device->IO->InputConnectors = (enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->IO->InputConnectors = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->IO->RelayOutputs = (enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->IO->RelayOutputs = xsd__boolean__false_;

	tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension = (struct tt__IOCapabilitiesExtension *)soap_malloc(soap, sizeof(struct tt__IOCapabilitiesExtension));
	tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->__size =0;
	tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->__any = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->Auxiliary = (enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->Auxiliary = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->__anyAttribute = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->__sizeAuxiliaryCommands = 0;
	tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->AuxiliaryCommands= NULL;
	tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->Extension = NULL;
#endif
#if 0
	tds__GetCapabilitiesResponse->Capabilities->Device->Security = (struct tt__SecurityCapabilities*)soap_malloc(soap, sizeof(struct tt__SecurityCapabilities));
	tds__GetCapabilitiesResponse->Capabilities->Device->Security->TLS1_x002e1 = (enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->Security->TLS1_x002e1 = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->Security->TLS1_x002e2 = (enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->Security->TLS1_x002e2 = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->Security->OnboardKeyGeneration = (enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->Security->OnboardKeyGeneration = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->Security->AccessPolicyConfig = (enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->Security->AccessPolicyConfig = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->Security->X_x002e509Token = (enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->Security->X_x002e509Token = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->Security->SAMLToken = (enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->Security->SAMLToken = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->Security->KerberosToken = (enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->Security->KerberosToken = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->Security->RELToken = (enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Device->Security->RELToken = xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Device->Security->Extension = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Device->Security->__size = 0;
	tds__GetCapabilitiesResponse->Capabilities->Device->Security->__any = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Device->Security->__anyAttribute = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Device->Extension = NULL;
#endif

	//想要对接RTSP视频，必须设置Media
	tds__GetCapabilitiesResponse->Capabilities->Media =
			(struct tt__MediaCapabilities*) soap_malloc(soap,
					sizeof(struct tt__MediaCapabilities));
	tds__GetCapabilitiesResponse->Capabilities->Media->XAddr =
			(char *) soap_malloc(soap, sizeof(char) * LARGE_INFO_LENGTH);
	strcpy(tds__GetCapabilitiesResponse->Capabilities->Media->XAddr,
			_IPv4Address);
	tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities =
			(struct tt__RealTimeStreamingCapabilities*) soap_malloc(soap,
					sizeof(struct tt__RealTimeStreamingCapabilities));
	tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTPMulticast =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTPMulticast =
			xsd__boolean__false_;
	tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORETCP =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORETCP =
			xsd__boolean__true_;
	tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORERTSP_USCORETCP =
			(enum xsd__boolean *) soap_malloc(soap, sizeof(enum xsd__boolean));
	*tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORERTSP_USCORETCP =
			xsd__boolean__true_;
	tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->Extension =
			NULL;
	tds__GetCapabilitiesResponse->Capabilities->Media->Extension = NULL;
	tds__GetCapabilitiesResponse->Capabilities->Media->__size = 0;
	tds__GetCapabilitiesResponse->Capabilities->Media->__any = 0;
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDPAddresses(struct soap* soap,
		struct _tds__SetDPAddresses *tds__SetDPAddresses,
		struct _tds__SetDPAddressesResponse *tds__SetDPAddressesResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetDPAddresses", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetHostname(struct soap* soap,
		struct _tds__GetHostname *tds__GetHostname,
		struct _tds__GetHostnameResponse *tds__GetHostnameResponse) {
	logInfo("__tds__GetHostname");
	tds__GetHostnameResponse->HostnameInformation =
			(struct tt__HostnameInformation*) soap_malloc(soap,
					sizeof(struct tt__HostnameInformation));
	tds__GetHostnameResponse->HostnameInformation->Name = (char*) soap_malloc(
			soap, INFO_LENGTH);
	tds__GetHostnameResponse->HostnameInformation->Extension =
			(struct tt__HostnameInformationExtension*) soap_malloc(soap,
					sizeof(struct tt__HostnameInformationExtension));

	tds__GetHostnameResponse->HostnameInformation->Extension->__size = 0;
	tds__GetHostnameResponse->HostnameInformation->Extension->__any = NULL;
	tds__GetHostnameResponse->HostnameInformation->FromDHCP = xsd__boolean__false_; //not from DHCP
	strcpy(tds__GetHostnameResponse->HostnameInformation->Name, HOST_NAME);
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetHostname(struct soap* soap,
		struct _tds__SetHostname *tds__SetHostname,
		struct _tds__SetHostnameResponse *tds__SetHostnameResponse) {
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetHostnameFromDHCP(
		struct soap* soap,
		struct _tds__SetHostnameFromDHCP *tds__SetHostnameFromDHCP,
		struct _tds__SetHostnameFromDHCPResponse *tds__SetHostnameFromDHCPResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetHostnameFromDHCP", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDNS(struct soap* soap,
		struct _tds__GetDNS *tds__GetDNS,
		struct _tds__GetDNSResponse *tds__GetDNSResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetDNS", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDNS(struct soap* soap,
		struct _tds__SetDNS *tds__SetDNS,
		struct _tds__SetDNSResponse *tds__SetDNSResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetDNS", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNTP(struct soap* soap,
		struct _tds__GetNTP *tds__GetNTP,
		struct _tds__GetNTPResponse *tds__GetNTPResponse) {
	logInfo("__tds__GetNTP");
	OnvifNTPInfo info;
	if (RET_CODE_SUCCESS != getNTPInfo(&info)) {
		return getOnvifSoapActionNotSupportCode(soap, "GetNTP",
						"get ntp info error");
	}
	struct tt__NTPInformation *pNTPInformation =
			(struct tt__NTPInformation*) soap_malloc(soap,
					sizeof(struct tt__NTPInformation));

	memset(pNTPInformation, 0, sizeof(struct tt__NTPInformation));

	// No support DHCP
	pNTPInformation->FromDHCP = xsd__boolean__false_;
	pNTPInformation->__sizeNTPFromDHCP = 0;
	pNTPInformation->__sizeNTPManual = 1;
	// Set NTP Manual parameter
	struct tt__NetworkHost *pNTPManual = (struct tt__NetworkHost*) soap_malloc(
			soap, sizeof(struct tt__NetworkHost));
	memset(pNTPManual, 0, sizeof(struct tt__NetworkHost));
	pNTPManual->Type = tt__NetworkHostType__IPv4;
	char pAddr[16] = {0};
	strcpy(pAddr, info.address);
	pNTPManual->IPv4Address = pAddr;
	pNTPInformation->NTPManual = pNTPManual;
	tds__GetNTPResponse->NTPInformation = pNTPInformation;
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNTP(struct soap* soap,
		struct _tds__SetNTP *tds__SetNTP,
		struct _tds__SetNTPResponse *tds__SetNTPResponse) {
	logInfo("__tds__SetNTP");
	if (xsd__boolean__true_ == tds__SetNTP->FromDHCP) {
		return getOnvifSoapActionNotSupportCode(soap, "SetNTP",
				"DHCPNotSupported");
	}
	if (tt__NetworkHostType__IPv4 == tds__SetNTP->NTPManual->Type)
	{
		char *pszIP = tds__SetNTP->NTPManual->IPv4Address;
		if (0 == ipOk(pszIP)) {
			OnvifNTPInfo ntpInfo;
			strcpy(ntpInfo.address, pszIP);
			int ret = setNTPInfo(&ntpInfo);
			if (RET_CODE_SUCCESS != ret) {
				return getOnvifSoapActionFailedCode(soap, "SetNTP",
									"set ntp failed");
			}
		} else {
			return getOnvifSoapActionFailedCode(soap, "SetNTP",
					"invalidIPv4Address IPv4");
		}
	} else if (tt__NetworkHostType__IPv6 == tds__SetNTP->NTPManual->Type) {
		return getOnvifSoapActionNotSupportCode(soap, "SetNTP",
				"No Support IPv6");
	} else if (tt__NetworkHostType__DNS == tds__SetNTP->NTPManual->Type) {
		return getOnvifSoapActionNotSupportCode(soap, "SetNTP",
				"No Support DNS");
	}
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDynamicDNS(struct soap* soap,
		struct _tds__GetDynamicDNS *tds__GetDynamicDNS,
		struct _tds__GetDynamicDNSResponse *tds__GetDynamicDNSResponse) {
	logInfo("__tds__GetDynamicDNS");
	return getOnvifSoapActionNotSupportCode(soap, "GetDynamicDNS", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDynamicDNS(struct soap* soap,
		struct _tds__SetDynamicDNS *tds__SetDynamicDNS,
		struct _tds__SetDynamicDNSResponse *tds__SetDynamicDNSResponse) {
	logInfo("__tds__SetDynamicDNS");
	return getOnvifSoapActionNotSupportCode(soap, "SetDynamicDNS", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNetworkInterfaces(
		struct soap* soap,
		struct _tds__GetNetworkInterfaces *tds__GetNetworkInterfaces,
		struct _tds__GetNetworkInterfacesResponse *tds__GetNetworkInterfacesResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetNetworkInterfaces", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNetworkInterfaces(
		struct soap* soap,
		struct _tds__SetNetworkInterfaces *tds__SetNetworkInterfaces,
		struct _tds__SetNetworkInterfacesResponse *tds__SetNetworkInterfacesResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetNetworkInterfaces", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNetworkProtocols(
		struct soap* soap,
		struct _tds__GetNetworkProtocols *tds__GetNetworkProtocols,
		struct _tds__GetNetworkProtocolsResponse *tds__GetNetworkProtocolsResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetNetworkProtocols", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNetworkProtocols(
		struct soap* soap,
		struct _tds__SetNetworkProtocols *tds__SetNetworkProtocols,
		struct _tds__SetNetworkProtocolsResponse *tds__SetNetworkProtocolsResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetNetworkProtocols", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNetworkDefaultGateway(
		struct soap* soap,
		struct _tds__GetNetworkDefaultGateway *tds__GetNetworkDefaultGateway,
		struct _tds__GetNetworkDefaultGatewayResponse *tds__GetNetworkDefaultGatewayResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetNetworkDefaultGateway", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNetworkDefaultGateway(
		struct soap* soap,
		struct _tds__SetNetworkDefaultGateway *tds__SetNetworkDefaultGateway,
		struct _tds__SetNetworkDefaultGatewayResponse *tds__SetNetworkDefaultGatewayResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetNetworkDefaultGateway", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetZeroConfiguration(
		struct soap* soap,
		struct _tds__GetZeroConfiguration *tds__GetZeroConfiguration,
		struct _tds__GetZeroConfigurationResponse *tds__GetZeroConfigurationResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetZeroConfiguration", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetZeroConfiguration(
		struct soap* soap,
		struct _tds__SetZeroConfiguration *tds__SetZeroConfiguration,
		struct _tds__SetZeroConfigurationResponse *tds__SetZeroConfigurationResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetZeroConfiguration", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetIPAddressFilter(
		struct soap* soap,
		struct _tds__GetIPAddressFilter *tds__GetIPAddressFilter,
		struct _tds__GetIPAddressFilterResponse *tds__GetIPAddressFilterResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetIPAddressFilter", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetIPAddressFilter(
		struct soap* soap,
		struct _tds__SetIPAddressFilter *tds__SetIPAddressFilter,
		struct _tds__SetIPAddressFilterResponse *tds__SetIPAddressFilterResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetIPAddressFilter", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__AddIPAddressFilter(
		struct soap* soap,
		struct _tds__AddIPAddressFilter *tds__AddIPAddressFilter,
		struct _tds__AddIPAddressFilterResponse *tds__AddIPAddressFilterResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "AddIPAddressFilter", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__RemoveIPAddressFilter(
		struct soap* soap,
		struct _tds__RemoveIPAddressFilter *tds__RemoveIPAddressFilter,
		struct _tds__RemoveIPAddressFilterResponse *tds__RemoveIPAddressFilterResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "RemoveIPAddressFilter", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetAccessPolicy(struct soap* soap,
		struct _tds__GetAccessPolicy *tds__GetAccessPolicy,
		struct _tds__GetAccessPolicyResponse *tds__GetAccessPolicyResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetAccessPolicy", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetAccessPolicy(struct soap* soap,
		struct _tds__SetAccessPolicy *tds__SetAccessPolicy,
		struct _tds__SetAccessPolicyResponse *tds__SetAccessPolicyResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetAccessPolicy", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__CreateCertificate(struct soap* soap,
		struct _tds__CreateCertificate *tds__CreateCertificate,
		struct _tds__CreateCertificateResponse *tds__CreateCertificateResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "CreateCertificate", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCertificates(struct soap* soap,
		struct _tds__GetCertificates *tds__GetCertificates,
		struct _tds__GetCertificatesResponse *tds__GetCertificatesResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetCertificates", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCertificatesStatus(
		struct soap* soap,
		struct _tds__GetCertificatesStatus *tds__GetCertificatesStatus,
		struct _tds__GetCertificatesStatusResponse *tds__GetCertificatesStatusResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetCertificatesStatus", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetCertificatesStatus(
		struct soap* soap,
		struct _tds__SetCertificatesStatus *tds__SetCertificatesStatus,
		struct _tds__SetCertificatesStatusResponse *tds__SetCertificatesStatusResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetCertificatesStatus", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__DeleteCertificates(
		struct soap* soap,
		struct _tds__DeleteCertificates *tds__DeleteCertificates,
		struct _tds__DeleteCertificatesResponse *tds__DeleteCertificatesResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "DeleteCertificates", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetPkcs10Request(struct soap* soap,
		struct _tds__GetPkcs10Request *tds__GetPkcs10Request,
		struct _tds__GetPkcs10RequestResponse *tds__GetPkcs10RequestResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetPkcs10Request", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__LoadCertificates(struct soap* soap,
		struct _tds__LoadCertificates *tds__LoadCertificates,
		struct _tds__LoadCertificatesResponse *tds__LoadCertificatesResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "LoadCertificates", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetClientCertificateMode(
		struct soap* soap,
		struct _tds__GetClientCertificateMode *tds__GetClientCertificateMode,
		struct _tds__GetClientCertificateModeResponse *tds__GetClientCertificateModeResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetClientCertificateMode", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetClientCertificateMode(
		struct soap* soap,
		struct _tds__SetClientCertificateMode *tds__SetClientCertificateMode,
		struct _tds__SetClientCertificateModeResponse *tds__SetClientCertificateModeResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetClientCertificateMode", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetRelayOutputs(struct soap* soap,
		struct _tds__GetRelayOutputs *tds__GetRelayOutputs,
		struct _tds__GetRelayOutputsResponse *tds__GetRelayOutputsResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetRelayOutputs", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRelayOutputSettings(
		struct soap* soap,
		struct _tds__SetRelayOutputSettings *tds__SetRelayOutputSettings,
		struct _tds__SetRelayOutputSettingsResponse *tds__SetRelayOutputSettingsResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetRelayOutputSettings", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRelayOutputState(
		struct soap* soap,
		struct _tds__SetRelayOutputState *tds__SetRelayOutputState,
		struct _tds__SetRelayOutputStateResponse *tds__SetRelayOutputStateResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetRelayOutputState", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SendAuxiliaryCommand(
		struct soap* soap,
		struct _tds__SendAuxiliaryCommand *tds__SendAuxiliaryCommand,
		struct _tds__SendAuxiliaryCommandResponse *tds__SendAuxiliaryCommandResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SendAuxiliaryCommand", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCACertificates(struct soap* soap,
		struct _tds__GetCACertificates *tds__GetCACertificates,
		struct _tds__GetCACertificatesResponse *tds__GetCACertificatesResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetCACertificates", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__LoadCertificateWithPrivateKey(
		struct soap* soap,
		struct _tds__LoadCertificateWithPrivateKey *tds__LoadCertificateWithPrivateKey,
		struct _tds__LoadCertificateWithPrivateKeyResponse *tds__LoadCertificateWithPrivateKeyResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "LoadCertificateWithPrivateKey", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCertificateInformation(
		struct soap* soap,
		struct _tds__GetCertificateInformation *tds__GetCertificateInformation,
		struct _tds__GetCertificateInformationResponse *tds__GetCertificateInformationResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetCertificateInformation", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__LoadCACertificates(
		struct soap* soap,
		struct _tds__LoadCACertificates *tds__LoadCACertificates,
		struct _tds__LoadCACertificatesResponse *tds__LoadCACertificatesResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "LoadCACertificates", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__CreateDot1XConfiguration(
		struct soap* soap,
		struct _tds__CreateDot1XConfiguration *tds__CreateDot1XConfiguration,
		struct _tds__CreateDot1XConfigurationResponse *tds__CreateDot1XConfigurationResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "CreateDot1XConfiguration", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDot1XConfiguration(
		struct soap* soap,
		struct _tds__SetDot1XConfiguration *tds__SetDot1XConfiguration,
		struct _tds__SetDot1XConfigurationResponse *tds__SetDot1XConfigurationResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "SetDot1XConfiguration", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot1XConfiguration(
		struct soap* soap,
		struct _tds__GetDot1XConfiguration *tds__GetDot1XConfiguration,
		struct _tds__GetDot1XConfigurationResponse *tds__GetDot1XConfigurationResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetDot1XConfiguration", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot1XConfigurations(
		struct soap* soap,
		struct _tds__GetDot1XConfigurations *tds__GetDot1XConfigurations,
		struct _tds__GetDot1XConfigurationsResponse *tds__GetDot1XConfigurationsResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetDot1XConfigurations", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__DeleteDot1XConfiguration(
		struct soap* soap,
		struct _tds__DeleteDot1XConfiguration *tds__DeleteDot1XConfiguration,
		struct _tds__DeleteDot1XConfigurationResponse *tds__DeleteDot1XConfigurationResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "DeleteDot1XConfiguration", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot11Capabilities(
		struct soap* soap,
		struct _tds__GetDot11Capabilities *tds__GetDot11Capabilities,
		struct _tds__GetDot11CapabilitiesResponse *tds__GetDot11CapabilitiesResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetDot11Capabilities", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot11Status(struct soap* soap,
		struct _tds__GetDot11Status *tds__GetDot11Status,
		struct _tds__GetDot11StatusResponse *tds__GetDot11StatusResponse) {
	return getOnvifSoapActionNotSupportCode(soap, "GetDot11Status", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__ScanAvailableDot11Networks(
		struct soap* soap,
		struct _tds__ScanAvailableDot11Networks *tds__ScanAvailableDot11Networks,
		struct _tds__ScanAvailableDot11NetworksResponse *tds__ScanAvailableDot11NetworksResponse) {
	logInfo("__tds__ScanAvailableDot11Networks");
	return getOnvifSoapActionNotSupportCode(soap, "ScanAvailableDot11Networks", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemUris(struct soap* soap,
		struct _tds__GetSystemUris *tds__GetSystemUris,
		struct _tds__GetSystemUrisResponse *tds__GetSystemUrisResponse) {
	logInfo("__tds__GetSystemUris");
	return getOnvifSoapActionNotSupportCode(soap, "GetSystemUris", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__StartFirmwareUpgrade(
		struct soap* soap,
		struct _tds__StartFirmwareUpgrade *tds__StartFirmwareUpgrade,
		struct _tds__StartFirmwareUpgradeResponse *tds__StartFirmwareUpgradeResponse) {
	logInfo("__tds__StartFirmwareUpgrade");
	return getOnvifSoapActionNotSupportCode(soap, "StartFirmwareUpgrade", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__StartSystemRestore(
		struct soap* soap,
		struct _tds__StartSystemRestore *tds__StartSystemRestore,
		struct _tds__StartSystemRestoreResponse *tds__StartSystemRestoreResponse) {
	logInfo("__tds__StartSystemRestore");
	return getOnvifSoapActionNotSupportCode(soap, "StartSystemRestore", NULL);
}

