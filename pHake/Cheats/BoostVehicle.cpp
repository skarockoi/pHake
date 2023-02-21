#include "../pLib/pUi/pOverlay.hpp"
#include "../SDK/World.hpp"
#include "../Settings.hpp"

#include "BoostVehicle.hpp"

#include <array>

static const std::array<std::string, 4> vehicle_modes = { "default", "race", "max", "fly" };
static uint8_t curr_vehicle_mode = 0;

static Vehicle vehicle_defaults;

BoostVehicle::BoostVehicle(std::shared_ptr<pOverlay> ui, std::shared_ptr<World> world)
{
	name_ = "BoostVehicle";
}

void BoostVehicle::Execute()
{
	if (vehicle_defaults.base() ^ world->localplayer.vehicle.base())
	{
		vehicle_defaults = world->localplayer.vehicle;
		curr_vehicle_mode = 0;
	}

	curr_vehicle_mode++;
	if (curr_vehicle_mode > vehicle_modes.size() - 1)
		curr_vehicle_mode = 0;

	switch (curr_vehicle_mode)
	{
	case 0:
		world->localplayer.vehicle.gravity(vehicle_defaults.gravity());
		world->localplayer.vehicle.handling.traction_max(vehicle_defaults.handling.traction_max());
		world->localplayer.vehicle.handling.traction_min(vehicle_defaults.handling.traction_min());
		world->localplayer.vehicle.handling.acceleration(vehicle_defaults.handling.acceleration());
		world->localplayer.vehicle.handling.collisiondamage(vehicle_defaults.handling.collisiondamage());
		break;
	case 1:
		world->localplayer.vehicle.gravity(20.f);
		world->localplayer.vehicle.handling.traction_max(3.f);
		world->localplayer.vehicle.handling.traction_min(3.f);
		world->localplayer.vehicle.handling.collisiondamage(0.f);
		world->localplayer.vehicle.handling.acceleration(3.f);
		break;
	case 2:
		world->localplayer.vehicle.gravity(25.f);
		world->localplayer.vehicle.handling.traction_max(5.f);
		world->localplayer.vehicle.handling.traction_min(5.f);
		world->localplayer.vehicle.handling.collisiondamage(0.f);
		world->localplayer.vehicle.handling.acceleration(20.f);
		break;
	case 3:
		world->localplayer.vehicle.gravity(-10.f);
		world->localplayer.vehicle.handling.traction_max(2.f);
		world->localplayer.vehicle.handling.traction_min(2.f);
		world->localplayer.vehicle.handling.collisiondamage(0.f);
		world->localplayer.vehicle.handling.acceleration(2.f);
		break;
	}
	 ui->notification.Add("Vehicle set to " + vehicle_modes[curr_vehicle_mode]);
}

void BoostVehicle::Restore()
{
	if (curr_vehicle_mode != 0)
	{
		world->localplayer.vehicle.gravity(vehicle_defaults.gravity());
		world->localplayer.vehicle.handling.traction_max(vehicle_defaults.handling.traction_max());
		world->localplayer.vehicle.handling.traction_min(vehicle_defaults.handling.traction_min());
		world->localplayer.vehicle.handling.acceleration(vehicle_defaults.handling.acceleration());
		world->localplayer.vehicle.handling.collisiondamage(vehicle_defaults.handling.collisiondamage());
	}
}