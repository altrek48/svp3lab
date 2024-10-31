#include <iostream>
#include <string>

using namespace std;

class IVehicle
{
public:
  virtual void drive(const int kilometers) = 0;
  virtual void refuel() = 0;
  virtual void printStatus() const = 0;
};

class AbstractCar : public IVehicle
{
protected:
  AbstractCar() : m_fuelConsumptionLitresPerKm(0.0), m_fuelLevel(0.0), m_fuelLevelMax(0.0), m_milageKm(0)
  {}

public:
  void drive(const int kilometers) override
  {
    const double requiredFuelLitres = ((double)kilometers) / 100.0 * m_fuelConsumptionLitresPerKm;
    if (requiredFuelLitres > m_fuelLevel)
    {
      cout << "Error: Not enough fuel to drive " << kilometers << " km" << endl;
      return;
    }
    cout << m_name << ": Drive " << kilometers << " km" << endl;
    m_milageKm += kilometers;
    m_fuelLevel -= requiredFuelLitres;
  }

  void refuel() override
  {
    cout << "Refuel " << m_name << endl;
    m_fuelLevel = m_fuelLevelMax;
  }

  void printStatus() const override
  {
    cout << m_name << " status: Mileage(km)=" << m_milageKm << ", Fuel level(l)=" << m_fuelLevel << endl;
  }

protected:
  double m_fuelConsumptionLitresPerKm;
  double m_fuelLevel;
  double m_fuelLevelMax;
  int m_milageKm;
  string m_name;
};

class Sedan : public AbstractCar
{
public:
  Sedan()
  {
    m_fuelConsumptionLitresPerKm = 7.0;
    m_fuelLevelMax = 50.0;
    m_name = "Sedan";
  }
};

class Suv : public AbstractCar
{
public:
  Suv()
  {
    m_fuelConsumptionLitresPerKm = 11.0;
    m_fuelLevelMax = 80.0;
    m_name = "Suv";
  }
};

class Bus : public AbstractCar
{
public:
  Bus()
  {
    m_fuelConsumptionLitresPerKm = 25.0;
    m_fuelLevelMax = 120.0;
    m_name = "Bus";
  }
};

class Bicycle : public IVehicle
{
public:
  Bicycle() : m_milageKm(0), m_name("Bicycle") {}

  void drive(const int kilometers) override
  {
    m_milageKm += kilometers;
  }

  void refuel() override {}

  void printStatus() const override
  {
    cout << m_name << " status: Mileage(km)=" << m_milageKm << endl;
  }

private:
  int m_milageKm;
  string m_name;
};

int main()
{
  IVehicle* vehicles[4] = {new Sedan, new Suv, new Bus, new Bicycle};
  for (int i = 0; i < 4; ++i)
  {
    IVehicle* vehicle = vehicles[i];
    vehicle->refuel();
    vehicle->printStatus();
    vehicle->drive(120);
    vehicle->printStatus();
    vehicle->drive(420);
    vehicle->printStatus();
    vehicle->drive(300);
    vehicle->printStatus();
    vehicle->refuel();
    vehicle->drive(300);
    vehicle->printStatus();
    delete vehicle;
    cout << endl;
  }
  return 0;
}
