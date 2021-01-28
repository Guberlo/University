<?php

use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', function () {
    return view('welcome');
});

Route::resource('/museums', App\Http\Controllers\MuseumController::class);

Route::resource('/paintings', App\Http\Controllers\PaintingController::class);

Route::resource('/authors', App\Http\Controllers\AuthorController::class);

