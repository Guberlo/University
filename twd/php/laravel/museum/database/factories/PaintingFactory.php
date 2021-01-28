<?php

namespace Database\Factories;

use App\Models\Painting;
use Illuminate\Database\Eloquent\Factories\Factory;
use App\Models\Author;
use App\Models\Museum;

class PaintingFactory extends Factory
{
    /**
     * The name of the factory's corresponding model.
     *
     * @var string
     */
    protected $model = Painting::class;

    /**
     * Define the model's default state.
     *
     * @return array
     */
    public function definition()
    {
        return [
            'author_id' => Author::factory(),
            'museum_id' => Museum::factory(),
            'title' => $this->faker->catchPhrase,
            'description' => $this->faker->sentence,
            'year_of_production' => $this->faker->year
        ];
    }
}
