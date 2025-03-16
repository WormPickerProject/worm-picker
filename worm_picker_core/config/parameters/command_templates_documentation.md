# WormPicker Command Reference

## Overview
This document provides a comprehensive reference for all command templates supported by the WormPicker system. Each command follows a colon-separated format and can be extended with optional speed override parameters.

## Command Structure  
All commands follow the format:  

`baseCommand[:arg1][:arg2]...[:velocity][:acceleration]`  

- **`baseCommand`** – The main command being executed  
- **`arg1, arg2, ...`** – Command-specific arguments  
- **`velocity`** – (Optional) Movement velocity scaling factor  
- **`acceleration`** – (Optional) Movement acceleration scaling factor  

### Speed Override Parameters  
All movement commands support optional **speed override parameters** to control motion scaling.  

#### Parameters:  
- **`velocity`** – Scales movement velocity  
  - **Range:** `(0.001, 0.999]`  
  - **Default:** `0.1`  
- **`acceleration`** – Scales movement acceleration  
  - **Range:** `(0.001, 0.999]`  
  - **Default:** `0.1`  


## Command Categories

### Zero Argument Commands
Commands that take no required arguments.

### Base Command: `home`
Moves all joints to the **zero position**.  
#### Syntax 
- **Basic:** `home`
- **Speed Override:** `home:velocity:acceleration`
#### Example
- `home:0.5:0.5`

### Base Command: `homeEndFactor`
Sets **joint 5** to **-30°**, effectively leveling the **plate pick**.  
#### Syntax  
- **Basic:** `homeEndFactor`  
- **Speed Override:** `homeEndFactor:velocity:acceleration`  
#### Example  
- `homeEndFactor:0.3:0.4`  

### Base Command: `moveToX`
Moves the **plate pick** to predefined workspace positions for **calibration**.
#### Syntax:
- **Basic:** `moveToX`  
- **Speed Override:** `moveToX:velocity:acceleration`
#### Available Commands:
- `moveToA2`
- `moveToM2`
- `moveToG4`
- `moveToG1`
- `moveToI1`
- `moveToE1`
- `moveToJ3`
- `moveToD3`
- `moveToI3`
- `moveToE3`
#### Example:
- `moveToA2:0.5:0.5`

## One Argument Commands
Commands that take a single required argument.

### Base Command: `pickPlateWorkStation`
```
Basic:           pickPlateWorkStation:PLATE
Speed Override:  pickPlateWorkStation:PLATE:velocity:acceleration
```

### Base Command: `placePlateWorkStation`
```
Basic:           placePlateWorkStation:PLATE
Speed Override:  placePlateWorkStation:PLATE:velocity:acceleration
```

### Base Command: `swapEndFactor`
```
Basic:           swapEndFactor:FACTOR
Speed Override:  swapEndFactor:FACTOR:velocity:acceleration
```

### Base Command: `hoverWormPick`
```
Basic:           hoverWormPick:PLATE
Speed Override:  hoverWormPick:PLATE:velocity:acceleration
```

### Base Command: `moveToPoint`
```
Basic:           moveToPoint:PLATE
Speed Override:  moveToPoint:PLATE:velocity:acceleration
```

## Three Argument Commands
Commands that take three required arguments.

### Base Command: `moveRelative`
```
Basic:           moveRelative:X:Y:Z
Speed Override:  moveRelative:X:Y:Z:velocity:acceleration
```

## Four Argument Commands
Commands that take four required arguments.

### Base Command: `moveAbsolutePos`
```
Basic:           moveAbsolutePos:X:Y:Z:TYPE
Speed Override:  moveAbsolutePos:X:Y:Z:TYPE:velocity:acceleration
```

## Eight Argument Commands
Commands that take eight required arguments.

### Base Command: `moveAbsolutePose`
```
Basic:           moveAbsolutePose:X:Y:Z:QX:QY:QZ:QW:TYPE
Speed Override:  moveAbsolutePose:X:Y:Z:QX:QY:QZ:QW:TYPE:velocity:acceleration
```

## Variable Argument Commands
Commands that can take a variable number of arguments based on a count prefix.

### Base Command: `moveRelative` (Variable Form)
```
Basic:           moveRelative:N=count:X1:Y1:Z1:X2:Y2:Z2:...:Xn:Yn:Zn
Speed Override:  moveRelative:N=count:X1:Y1:Z1:X2:Y2:Z2:...:Xn:Yn:Zn:velocity:acceleration
```

Note: For the variable form of `moveRelative`, the `N=count` specifies how many sets of X:Y:Z coordinates follow. Each set represents a point in the relative movement sequence.