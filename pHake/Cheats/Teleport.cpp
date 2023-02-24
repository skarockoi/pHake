#include "../pLib/pUi/pOverlay.hpp"
#include "../pLib/pHelper.hpp"
#include "../pLib/pMemory/vec3.hpp"
#include "../SDK/World.hpp"

#include "Teleport.hpp"


Teleport::Teleport(std::shared_ptr<pOverlay> ui, std::shared_ptr<World> world, std::shared_ptr<pProcess> process, std::shared_ptr<Settings> settings)
{
	this->ui = ui;
	this->process = process;
	this->world = world;
	this->settings = settings;

	name_ = "Tp to Waypoint";
}

void Teleport::Execute()
{
	vec3 waypoint = process->read<vec3>(settings->pointers.waypoint);

	if (waypoint.x == 64000 && waypoint.y == 64000) {
		ui->notification.Add("No Waypoint set");
		return;
	}

	if (world->localplayer.in_vehicle())
	{
		if (IsVehicleMoving())
		{
			ui->notification.Add("Don't move");
			return;
		}

		waypoint.z = -210.f;
		world->localplayer.vehicle.position.xyz(waypoint);
		Move();

		goto success;
	}

	if (settings->noclip)
	{
		waypoint.z = 300.f;
		world->localplayer.position.xyz(waypoint);
		Move();

		goto success;
	}

	if (IsPlayerMoving())
	{
		ui->notification.Add("Don't move");
		return;
	}

	waypoint.z = -210.f;
	world->localplayer.position.xyz(waypoint);
	Move();

	goto success;

success:
	ui->notification.Add("Teleported to Waypoint");
	return;
}

void Teleport::Restore()
{
}

bool Teleport::IsPlayerMoving()
{
	if (world->localplayer.speed_xyz().len() > 0.1)
		return true;
	return false;
}

bool Teleport::IsVehicleMoving()
{
	if (world->localplayer.vehicle.speed_xyz().len() > 0.1)
		return true;
	return false;
}

void Teleport::Move()
{
	Key::Down::W();
	sleep(50);
	Key::Up::W();
}