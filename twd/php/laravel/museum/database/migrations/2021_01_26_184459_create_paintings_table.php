<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreatePaintingsTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('paintings', function (Blueprint $table) {
            $table->id();
            $table->foreignId('author_id');
            $table->foreignId('museum_id');
            $table->string('title');
            $table->text('description')->nullable();
            $table->string('year_of_production');
            $table->timestamps();

            $table->unique(['author_id', 'title', 'year_of_production']);

            $table->foreign('author_id')
            ->references('id')
            ->on('authors')
            ->onDelete('cascade');

            $table->foreign('museum_id')
            ->references('id')
            ->on('museums')
            ->onDelete('cascade');
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('paintings');
    }
}
