# Vaccine_Scheduler_Online_Algorithm

Project part of the Computing Science MSc Algorithms for Decision Support

## Problem description

In an unnamed small country the population is to be vaccinated for an unnamed
disease. In this assignment, the planning for giving the vaccination to the patients is to be made. There are a number of different aspects and constraints
that are taken to be into account:

• Global parameters, which are the same for all patients:
– the processing time of the first dose p1 ≥ 1,
– the processing time of the second dose p2 ≥ 1,
– and the time gap between the first and the second doses g.
• A set of jobs J = {J1, J2, · · · , Jn}. Each job represents one patient. Each
job has the following information:
– For job Ji ∈ J :
∗ The first feasible interval Ii,1 = [ri,1, di,1] for the first dose (given
by the patient)
∗ The first dose is scheduled at start time ti,1 ∈ Ii,1 such that
ti,1 + p1 − 1 ≤ di,1. (This value has to be determined by the
program.)
∗ The patient-dependent delay xi where xi ≥ 0.
∗ The patient-dependent (second) feasible interval length `i where
`i ≥ p2
∗ The second feasible interval Ii,2 = [ti,1+p1 +g +xi
, ti,1+p1 +g +
xi + `i−1] for the second dose. Note that this interval depends
on the start time for the first dose as was determined by the
program, and the given values g, xi
, and `i
.)
∗ The second dose is scheduled at start time [ti,2, ti,2 + p2 − 1] ∈
Ii,2. (This value also has to be determined by the program.)
• Machine (hospital): at any time step, there can be at most one job executing. I.e., at each time step, each hospital can have at most 1 patient
who received a dose or is in observation.
• Feasible schedule: For any job Ji
, the first dose is scheduled at time interval [ti,1, ti,1 + p1−1] ⊆ Ii,1, and the second dose is scheduled at time
[ti,2, ti,2 + p2−1] ⊆ Ii,2.
• Objective: Minimize the number of machines (i.e., hospitals).

The online problem and online algorithm work as follows. At the start, the
global parameters p1, p2, and g are given. Then, we have for each patient one
round. At round i, we obtain all information for the ith patient: these are four
integers, where the first two give the interval for the first dose, the third the
delay for this patient, and the fourth the length of the second feasible interval.
The program then has to schedule this patient: give the time and hospital when
and where the first dose is given, the time and hospital when and where the
second dose is given. 
