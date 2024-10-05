#include "ServiceStation.h"

ServiceStation ServiceStation::service; // Инициализация статического поля

ServiceStation& ServiceStation::getInstance() {
	return service;
}