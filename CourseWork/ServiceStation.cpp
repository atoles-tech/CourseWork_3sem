#include "ServiceStation.h"

ServiceStation ServiceStation::service; // ������������� ������������ ����

ServiceStation& ServiceStation::getInstance() {
	return service;
}