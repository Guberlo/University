<?php

use Illuminate\Support\Facades\Route;
use App\Http\Controllers\BookController;
use App\Http\Controllers\GenreController;
use App\Http\Controllers\UserController;

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

Route::get('/library', [BookController::class, 'index']);
Route::get('/library/create', [BookController::class, 'create'])->middleware('auth'); // If we switch order with show method we would get 404 not found
Route::get('/library/{book}', [BookController::class, 'show']);
Route::post('/library/create', [BookController::class, 'store'])->middleware('auth');

Route::get('/genres/{genre}', [GenreController::class, 'index']);

Route::get('/authors/{user}', [UserController::class, 'show']);

Auth::routes();
Route::get('/home', [App\Http\Controllers\HomeController::class, 'index'])->name('home');
