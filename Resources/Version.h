/*
Copyright (c) 2022, NVIDIA CORPORATION. All rights reserved.

NVIDIA CORPORATION and its licensors retain all intellectual property
and proprietary rights in and to this software, related documentation
and any modifications thereto. Any use, reproduction, disclosure or
distribution of this software and related documentation without an express
license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

/*
Versioning rules:
- give version to someone - increment version before and after for tracking
- BUILD - preserves binary compatibility
- MINOR - settings & descs change
- MAJOR - major feature update, API change
- don't forget to update README
*/

#define VERSION_MAJOR                   1
#define VERSION_MINOR                   85
#define VERSION_BUILD                   0
#define VERSION_REVISION                0

#define VERSION_STRING STR(VERSION_MAJOR.VERSION_MINOR.VERSION_BUILD.VERSION_REVISION)