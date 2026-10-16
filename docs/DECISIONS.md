# VOLTRA Echo: engineering decisions

These explain the **current inspectable design/documentation**, not why the owner originally bought components. Original selection history and personal debugging experiences have not been supplied.

| Decision | Current-file rationale | Alternative / trade-off | Constraint |
| --- | --- | --- | --- |
| Invalid differs from zero | A timeout clears samples instead of presenting a false near reading or stale range. | Holding the last value looks stable but can hide failure. | Presentation must explicitly retain invalid/stale states. |
| Small median window | Use a bounded outlier filter over three-to-five valid samples. | A mean is simpler but more sensitive to extremes. | Filtering adds latency; real error/response is unmeasured. |
| Hysteresis and freshness | Reduce threshold chatter and expire old data. | One threshold may oscillate; permanent last-value display hides outages. | No motion analysis or safety function is established. |

## Challenges: distinguish observed from suggested

The tests and configuration guards establish specific reference-software behavior, not proof that those failures occurred on the owner's prototype. The original matching sketch was not recovered.

No actual accuracy, target reliability, motion analysis or safe obstacle-avoidance performance was measured.

Troubleshooting suggestions are hypotheses, not incidents already solved. Add a case study only with the observed symptom, reproducible conditions, evidence for the cause, exact change, before/after test and remaining uncertainty. Do not turn design intentions into measured improvements.

[Architecture](ARCHITECTURE.md) · [Validation record](VALIDATION.md)
