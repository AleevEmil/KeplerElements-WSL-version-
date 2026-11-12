import numpy as np
import orbit_py

mu = 398600.4418  # км^3/с^2

r0 = np.array([7000.0, 0.0, 0.0])
v0 = np.array([0.0, np.sqrt(mu / 7000.0), 0.0])
T = 2.0 * np.pi * np.sqrt(7000.0**3 / mu)

r1, v1 = orbit_py.predict_orbit(r0, v0, T, mu)

print("--- Прогноз на полный период ---")
print(f"r0: {r0}")
print(f"r1: {r1}")
print(f"Ошибка по положению: {np.linalg.norm(r1 - r0):.2e}")

kep = orbit_py.rv_to_kep(r1, v1, mu)
print("\n--- Элементы Кеплера ---")
print(f"a:    {kep.a:.3f} км")
print(f"e:    {kep.e:.4e}")
print(f"i:    {np.degrees(kep.i):.3f} град")
print(f"RAAN: {np.degrees(kep.RAAN):.3f} град")
print(f"w:    {np.degrees(kep.w):.3f} град")
print(f"nu:   {np.degrees(kep.nu):.3f} град")

r2, v2 = orbit_py.kep_to_rv(kep, mu)
print(f"\nОшибка после round-trip: {np.linalg.norm(r2 - r1):.2e}")