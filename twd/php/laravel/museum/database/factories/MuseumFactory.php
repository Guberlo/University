<?php

namespace Database\Factories;

use App\Models\Museum;
use Illuminate\Database\Eloquent\Factories\Factory;

class MuseumFactory extends Factory
{
    /**
     * The name of the factory's corresponding model.
     *
     * @var string
     */
    protected $model = Museum::class;

    /**
     * Define the model's default state.
     *
     * @return array
     */
    public function definition()
    {
        return [
            'name' => $this->faker->company,
            'city' => $this->faker->city
        ];
    }
}
