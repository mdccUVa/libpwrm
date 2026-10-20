// libpwrm: Library for monitoring CPU and GPU power usage and energy consumption.
// Copyright (C) 2026  Manuel de Castro <manuel@infor.uva.es>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// and GNU Lesser General Public License along with this program.
// If not, see <https://www.gnu.org/licenses/>.

#ifndef POWER_METER_H
#define POWER_METER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/// Result type for libpwrm functions that may fail.
typedef enum PwrmError {
	/// The function executed without errors.
	PWRM_SUCCESS = 0,
	/// The specified feature is not enabled for this system and/or library configuration.
	PWRM_FEATURE_NOT_ENABLED = -1,
	/// The provided path is erroneous.
	PWRM_PATH_ERROR = -2,
	/// There was an unspecified error during monitoring.
	PWRM_MONITORING_ERROR = -3,
	/// Not enough measures have been taken to provide energy or power results.
	PWRM_NOT_ENOUGH_DATA = -4,
} pwrmResult_t;

/// Starts monitoring the power usage and energy consumption of the system's CPU and GPU
/// at the specified sampling interval (in milliseconds).
void pwrm_launch_monitoring_loop(uint64_t sampling_interval_ms);
/// Stops monitoring the power usage and energy consumption of the system.
pwrmResult_t pwrm_stop_monitoring_loop(void);
/// Gets the CPU's average power usage since monitoring started or the last counters reset:
pwrmResult_t pwrm_get_avg_cpu_power(double *avg_power_out);
/// Gets the GPU's average power usage since monitoring started or the last counters reset:
pwrmResult_t pwrm_get_avg_gpu_power(double *avg_power_out);
/// Gets the CPU's total energy consumption since monitoring started or the last counters reset:
pwrmResult_t pwrm_get_total_cpu_energy(double *total_energy_out);
/// Gets the CPU's total energy consumption since monitoring started or the last counters reset:
pwrmResult_t pwrm_get_total_gpu_energy(double *total_energy_out);
/// Resets the power usage and energy consumption counters to zero, discarding all
/// previously collected data:
void pwrm_reset_counters(void);
/// Sets the path of the output directory where the measured data will be saved
/// (optional, "power_meter_out" by default, NULL uses the current directory).
pwrmResult_t pwrm_set_output_dir(const char *path_ptr);
/// Sets the name for the output file containing the CPU data
/// (optional, "cpu" by default; NULL or "" deactivate it).
pwrmResult_t pwrm_set_cpu_out_filename(const char *filename_ptr);
/// Sets the name for the output file containing the GPU data
/// (optional, "gpu" by default; NULL or "" deactivate it).
pwrmResult_t pwrm_set_gpu_out_filename(const char *filename_ptr);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // POWER_METER_H
