<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use App\Models\Painting;

class Author extends Model
{
    use HasFactory;

    protected $guarded = [];
    
    public function paintings() {
        return $this->hasMany(Painting::class);
    }
}
