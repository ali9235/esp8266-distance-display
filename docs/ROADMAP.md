# VOLTRA Echo: development roadmap

Status at documentation preparation, 16 October 2026. Future items are not completed features, deadlines or a claim that a hardware campaign is underway.

## Completed and inspectable

- Real prototype photographs and explicit evidence boundaries.
- New reference firmware, portable core tests, hardware-disabled defaults and compiler evidence.
- Source-grounded explanations and a genuine-media/evidence record.

## Prepared for review

The VOLTRA Engineering Standard documentation, local checks and proposed CI configuration are prepared together. No semantic tag, GitHub Release or passing Actions run is implied. See [release management](RELEASING.md).

## Next, in dependency order

1. Identify sensor, supply and echo logic level; document traced GPIOs.
2. Collect repeated known stationary distances with units/timestamps.
3. Test soft/angled targets, no echo and interruption/recovery; keep failures.
4. Measure uncertainty and response before selecting application thresholds.

## Acceptance gates

Hardware milestones need identified parts, a recorded revision, traced wiring, raw observations with units and genuine footage. Report failures alongside successes. Accuracy, power, latency and endurance stay unmeasured until supported by a real record.

No actual accuracy, target reliability, motion analysis or safe obstacle-avoidance performance was measured.

[Validation](VALIDATION.md) · [Changelog](../CHANGELOG.md)
