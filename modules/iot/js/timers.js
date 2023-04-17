/* Copyright 2023 EVM team
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
var timer = require('@native.timer');

function Timer() {
    this.handle = timer.create();
}

Timer.prototype.start = function(period, repeat) {
    timer.start(this.handle, period, repeat)
}

Timer.prototype.stop = function() {
    timer.stop(this.handle)
}

Timer.prototype.on = function(callback) {
    this.handle.handleTimeout = callback
}

function _setTimeout(callback, time) {
    var t = new Timer()
    t.on(callback);
    t.start(time, false);
    t.start();
    return t;
}

function _clearTimeout(timer) {
    timer.stop();
}

globalThis.setTimeout = _setTimeout;
globalThis.clearTimeout = _clearTimeout;
