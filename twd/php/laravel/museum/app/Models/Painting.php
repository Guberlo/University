<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use App\Models\Museum;
use App\Models\Author;

class Painting extends Model
{
    use HasFactory;

    protected $guarded = [];

    public function museum() {
        return $this->belongsTo(Museum::class);
    }

    public function author() {
        return $this->belongsTo(Author::class);
    }
}
