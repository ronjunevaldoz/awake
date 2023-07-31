# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.0.0-SNAPSHOT] - YYYY-MM-DD

### TODO

- [ ] Render triangle via Vulkan (Android, iOS, Desktop)
- [ ] To improve game loop
- [ ] Implement Fixed & Variable timestep
- [ ] Create ECS (Entity, Component, System)
- [ ] Create renderer that can draw single and batch instance
- [ ] Model instancing to provide faster rendering for batch models
- [ ] Animation instancing to provide faster rendering for batch model with animations
- [ ] UI Text, etc. (similar to compose-ui??)
- [ ] Physics Networking (low priority)

### Changes

- Improve vulkan struct to java vice-versa converter

### Added

- Vulkan Android support.
- Initial support for Android, iOS, and desktop OpenGL.
- Implemented using Compose Multiplatform for increased flexibility.
- Experimental high-quality text rendering (TTF).

### Known Issues

- Vulkan validation error (VkDeviceQueueCreateInfo-pQueuePriorities ) is not between 0 and 1 (
  inclusive) actual device (Tested only in Xiaomi MI lite 12)
- Possible memory leak when using Vulkan.
- Incomplete text rendering.
- Desktop OpenGL texture rendering is leaking.

[unreleased]: https://github.com/ronjunevaldoz/awake/compare/v1.0.0...HEAD

[1.0.0-SNAPSHOT]: https://github.com/ronjunevaldoz/awake/compare/v0.0.1...v0.0.2